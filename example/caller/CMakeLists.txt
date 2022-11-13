# set(SRC_LIST calluserservice.cc ../user.pb.cc)
set(SRC_LIST callfriendservice.cc ../friends.pb.cc)

add_executable(consumer ${SRC_LIST}) # 可执行文件

target_link_libraries(consumer mprpc protobuf pthread)

