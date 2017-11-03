using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Diagnostics;

public class ABGraphNode {
    public string path;
    public int reference;
    public List<ABGraphNode> parents = new List<ABGraphNode>();
    public List<ABGraphNode> children = new List<ABGraphNode>();

    public void RemoveChild(ABGraphNode child) {
        child.parents.Remove(this);
        this.children.Remove(child);
    }

    public List<ABGraphNode> GetAllChildren(List<ABGraphNode> excepts = null) {
        List<ABGraphNode> ret = new List<ABGraphNode>();
        foreach(var child in children) {
            if (excepts == null || !excepts.Contains(child)) {
                ret.Add(child);
            }
            ret.AddRange(child.GetAllChildren(excepts));
        }
        return ret;
    }

    public override string ToString() {
        return path;
    }
}

public class ABContent {
    public const string scriptABName = "ab_scripts";
    public const string shaderABName = "ab_shaders";

    public string name;
    public bool persistent = false;
    public List<ABGraphNode> nodes = new List<ABGraphNode>();
    public bool ContainPath(string path) {
        foreach (var node in nodes) {
            if (node.path == path)
                return true;
            var children = node.GetAllChildren();
            if (children.Count > 0) {
                foreach (var child in children) {
                    if (child.path == path)
                        return true;
                }
            }
        }
        return false;
    }

    public List<string> GetAllPaths() {
        List<string> ret = new List<string>();
        foreach(var node in nodes) {
            ret.Add(node.path);
            var children = node.GetAllChildren();
            if (children.Count > 0) {
                foreach (var child in children) {
                    ret.Add(child.path);
                }
            }
        }
        return ret;
    }

    bool IsScene(string path) {
        return path.EndsWith(".unity");
    }

    public string GetScene() {
        List<string> ret = new List<string>();
        foreach (var node in nodes) {
            if (IsScene(node.path))
                return node.path;
            var children = node.GetAllChildren();
            if (children.Count > 0) {
                foreach (var child in children) {
                    if (IsScene(child.path))
                        return child.path;
                }
            }
        }
        return string.Empty;
    }

    public List<string> GetAllPathsWithoutScene() {
        List<string> ret = new List<string>();
        foreach (var node in nodes) {
            if(!IsScene(node.path))
                ret.Add(node.path);
            var children = node.GetAllChildren();
            if (children.Count > 0) {
                foreach (var child in children) {
                    if(!IsScene(child.path))
                        ret.Add(child.path);
                }
            }
        }
        return ret;
    }
}


public class ABGraph {
    private Dictionary<string, OneResource> mRawResourceMap;

    ResourceSet LoadJsonObject(string content) {
#if UNITY_EDITOR
        return UnityEngine.JsonUtility.FromJson<ResourceSet>(content);
#else
        return Newtonsoft.Json.JsonConvert.DeserializeObject<ResourceSet>(content);
#endif

    }

    public Dictionary<string, OneResource> LoadResourceMap(string path) {
        string content = File.ReadAllText(path);
        var set = LoadJsonObject(content);
        Dictionary<string, OneResource> map = new Dictionary<string, OneResource>();
        Dictionary<string, OneResource> ret = new Dictionary<string, OneResource>();
        foreach (var res in set.resources)
            map.Add(res.path, res);

        foreach (var kv in map) {
            kv.Value.path = kv.Value.path.Replace('\\', '/').ToLower();
            for (int i = 0; i < kv.Value.dependices.Count; ++i) {
                kv.Value.dependices[i] = kv.Value.dependices[i].ToLower();
            }
            kv.Value.dependices.Remove(kv.Value.path);
            ret.Add(kv.Key.Replace('\\', '/').ToLower(), kv.Value);
        }
        return ret;
    }

    public List<ABGraphNode> LoadFromJson(string path) {
        mRawResourceMap = LoadResourceMap(path);
        var hierarchyMap = CreateHierarchy(mRawResourceMap);
        var nodes = CreateGraph(hierarchyMap);
        return nodes;
    }

    public string GetABName(string path, out bool persistent) {
        string abName = path;
        if (path.EndsWith(".txt")) {
            abName = ABContent.scriptABName;
            persistent = true;
        } else if (path.EndsWith(".shader")) {
            abName = ABContent.shaderABName;
            persistent = true;
        } else {
            persistent = false;
        }
        return abName;
    }

    public List<ABContent> GenerateContent(List<ABGraphNode> nodes) {
        Dictionary<string, ABContent> contentMap = new Dictionary<string, ABContent>();
        List<ABContent> ret = new List<ABContent>();

        HashSet<string> checkSet = new HashSet<string>();

        foreach (var node in nodes) {
            ABContent content = null;
            bool persistent = false;
            string abName = GetABName(node.path, out persistent);
            if (!contentMap.TryGetValue(abName, out content)) {
                content = new ABContent();
                content.name = abName;
                contentMap.Add(abName, content);
                content.persistent = persistent;
            }
            content.nodes.Add(node);
        }
        ret.AddRange(contentMap.Values);
        int resourceCount = 0;

        foreach(var content in ret) {
            foreach (var node in content.nodes) {
                var children = node.GetAllChildren();
                resourceCount += children.Count + 1;
                foreach(var child in children) {
                    Debug.Assert(checkSet.Add(child.path));
                }
            }
        }

        Debug.Assert(resourceCount == mRawResourceMap.Count);

        foreach (var res in mRawResourceMap)
            Debug.Assert(CheckNode(res.Key, contentMap));

        return ret;
    }

    bool CheckNode(string path, Dictionary<string, ABContent> contentMap) {
        foreach(var content in contentMap) {
            if (content.Value.ContainPath(path))
                return true;
        }
        return false;
    }

    bool IsOnlyOneOrZeroParentNode(ABGraphNode node, out ABGraphNode ret, List<ABGraphNode> closedList = null) {
        if (node.parents.Count > 1) {
            ret = node;
            return false;
        }

        if (closedList == null)
            closedList = new List<ABGraphNode>();

        if (node.children.Count > 0) {
            var children = node.GetAllChildren(closedList);
            foreach (var child in children) {
                if (!IsOnlyOneOrZeroParentNode(child, out ret, closedList))
                    return false;
            }
        }
        if (node.parents.Count == 0) {
            ret = node;
            closedList.Add(node);
            return true;
        } else {
            closedList.Add(node);
            ABGraphNode parent = node.parents[0];
            var children = parent.GetAllChildren(closedList);
            foreach (var child in children) {
                if (!IsOnlyOneOrZeroParentNode(child, out ret, closedList))
                    return false;
            }
            closedList.Add(parent);
            return IsOnlyOneOrZeroParentNode(parent, out ret, closedList);
        }
    }

    List<ABGraphNode> CreateGraph(Dictionary<string, ABGraphNode> nodeMap) {
        List<ABGraphNode> ret = new List<ABGraphNode>();
        while(nodeMap.Count > 0) {
            var kv = nodeMap.First();
            ABGraphNode node = kv.Value;
            ABGraphNode outNode = null;
            if (IsOnlyOneOrZeroParentNode(node, out outNode)) {
                if (outNode.children.Count > 0) {
                    foreach(var child in outNode.GetAllChildren(null))
                        nodeMap.Remove(child.path);
                }
            } else {
                while(outNode.parents.Count > 0)
                    outNode.parents[0].RemoveChild(outNode);
                var children = outNode.GetAllChildren();
                foreach (var child in children) {
                    ABGraphNode childoutnode = null;
                    if(IsOnlyOneOrZeroParentNode(child, out childoutnode))
                        nodeMap.Remove(child.path);
                }
            }
            nodeMap.Remove(outNode.path);
            Debug.Assert(!ret.Contains(outNode));
            ret.Add(outNode);
        }

        int nodecount = 0;
        foreach (var node in ret) {
            Debug.Assert(node.parents.Count <= 1);
            var children = node.GetAllChildren();
            nodecount += children.Count + 1;
            foreach (var child in children)
                Debug.Assert(child.parents.Count == 1);
        }

        Debug.Assert(nodecount == mRawResourceMap.Count);

        return ret;
    }

    public Dictionary<string, ABGraphNode> CreateHierarchy(Dictionary<string, OneResource> map) {
        Dictionary<string, ABGraphNode> rawNodeMap = new Dictionary<string, ABGraphNode>();

        foreach (var kv in map) {
            var resource = kv.Value;
            ABGraphNode graphNode = null;
            if (!rawNodeMap.TryGetValue(resource.path, out graphNode)) {
                graphNode = new ABGraphNode();
                graphNode.path = resource.path;
                graphNode.reference = resource.reference;
                rawNodeMap.Add(resource.path, graphNode);
            }
            if(resource.dependices.Count > 0)
                AddChildNode(graphNode, resource.dependices, map, rawNodeMap);
        }

        Debug.Assert(map.Count == rawNodeMap.Count);
        return rawNodeMap;
    }

    void AddChildNode(ABGraphNode parent, List<string> childPaths, Dictionary<string, OneResource> map, Dictionary<string, ABGraphNode> rawNodeMap) {
        List<OneResource> childResources = new List<OneResource>();
        foreach (var path in childPaths) {
            childResources.Add(map[path]);
        }

        var minResource  = childResources.Min();
        List<OneResource> minResources = new List<OneResource>();
        foreach(var res in childResources) {
            if (res.reference == minResource.reference)
                minResources.Add(res);
        }

        foreach(var item in minResources) {
            ABGraphNode graphNode = null;
            if (!rawNodeMap.TryGetValue(item.path, out graphNode)) {
                graphNode = new ABGraphNode();
                graphNode.path = item.path;
                graphNode.reference = item.reference;
                rawNodeMap.Add(item.path, graphNode);
            }
            if (graphNode.parents.Find((n) => n.path == parent.path) != null)
                return;
            graphNode.parents.Add(parent);
            if (parent.children.Find((n) => n.path == graphNode.path) != null)
                return;
            parent.children.Add(graphNode);

            if (item.dependices.Count > 0) {
                AddChildNode(graphNode, item.dependices, map, rawNodeMap);
            }
        }

    }
}
