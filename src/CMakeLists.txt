# aux_source_directory(. SRC_LIST)
set(SRC_LIST
    mprpcapplication.cc
    mprpcprovider.cc
    mprpcconfig.cc
    mprpcheader.pb.cc
    mprpcchannel.cc
    mprpccontroller.cc
    mprpclogger.cc
    zookeeperutil.cc
)

aux_source_directory(./muduo MUDUO_LIST)
add_library(mprpc ${SRC_LIST} ${MUDUO_LIST})
target_link_libraries(mprpc pthread zookeeper_mt)