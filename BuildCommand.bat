cd CS
::客户端使用protobuf-net
::后端使用protobuf-cpp-3.0.0
protoc  --cpp_out=../SLinux/Servers/pkg Command.proto
protoc  --cpp_out=../SLinux/Servers/pkg Cmd.proto
protoc  --cpp_out=../SLinux/Servers/pkg GameDefine.proto
protogen  -i:Command.proto -o:../C/Client/Assets/Scripts/Command.cs 
protogen  -i:Cmd.proto -o:../C/Client/Assets/Scripts/Cmd.cs
protogen  -i:GameDefine.proto -o:../C/Client/Assets/Scripts/GameDefine.cs
pause 