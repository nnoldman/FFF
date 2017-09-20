cd CS
::客户端使用protobuf-net
::后端使用protobuf-cpp-3.0.0
protoc  --cpp_out=../S/PKG Command.proto
protoc  --cpp_out=../S/PKG Cmd.proto
protoc  --cpp_out=../S/PKG GameDefine.proto
protogen  -i:Command.proto -o:../C/Client/Assets/Scripts/Command.cs 
protogen  -i:Cmd.proto -o:../C/Client/Assets/Scripts/Cmd.cs
protogen  -i:Cmd.proto -o:../C/Client/Assets/Scripts/GameDefine.cs
pause 