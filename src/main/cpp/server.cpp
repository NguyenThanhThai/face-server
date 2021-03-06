
#include <protocol/TBinaryProtocol.h>
#include <server/TNonblockingServer.h>
#include <transport/TServerSocket.h>
#include <transport/TBufferTransports.h>
#include <concurrency/ThreadManager.h>
#include <concurrency/PlatformThreadFactory.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/param.h>
#include <unistd.h>

#include <boost/program_options.hpp>
#include "FaceServiceImpl.h"


using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;

using boost::shared_ptr;

namespace po = boost::program_options;

using namespace std;

int main(int argc, char *argv[]) {
    int port = 3700;
    int threads = 4;
    try {
        po::options_description desc("Face Server options");
        desc.add_options()
                ("help", "produce this help message")
                ("port", po::value<int>(&port)->default_value(port), "listen port number (default 3700)")
                ("thread", po::value<int>(&threads)->default_value(threads), "number of threads (default 4)")
                ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            cout << desc << "\n";
            return 1;
        }
    } catch (exception& e) {
        cerr << "error parsing command line: " << e.what() << "\n";
        return 1;
    } catch (...) {
        cerr << "Exception of unknown type in parsing command line!\n";
        return 1;
    }
    
    FaceServiceImpl isHandler(threads);
    
    shared_ptr<FaceServiceImpl> handler(&isHandler);
    
    FaceServiceProcessor isProcessor(handler);
    shared_ptr<TProcessor> processor(&isProcessor);
    //shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    //shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    TBinaryProtocolFactory binaryProtocolFactory;
    shared_ptr<TProtocolFactory> protocolFactory(&binaryProtocolFactory);


    //create platform thread factory, can be Posix or Boost thread factory
    PlatformThreadFactory platformThreadFactory;
    shared_ptr<PlatformThreadFactory> threadFactory(&platformThreadFactory);

    shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(threads);
    threadManager->threadFactory(threadFactory);
    threadManager->start();

    TNonblockingServer server(processor, protocolFactory, port, threadManager);

    cout << "Face server (v1.0): "<< threads<<" threads"
         << ", port:"<< port <<"\n";

    server.serve();

    threadManager->stop();
    
    return 0;
}
