from xmlrpc.server import SimpleXMLRPCServer

def find_factorial(n):
    ans = 1
    for i in range(1, n+1):
        ans = ans * i
    return ans


def find_square(n):
    squa = n*n
    return squa


port = 1609
server = SimpleXMLRPCServer(("localhost", port), logRequests = False)
server.register_function(find_factorial, 'find_factorial_rpc')
server.register_function(find_square, 'find_square_rpc')

try:
    print("Starting and listening on the Port", port)
    server.serve_forever()

except:
    print("Exit")