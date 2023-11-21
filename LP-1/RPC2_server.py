import xmlrpc.client
proxy = xmlrpc.client.ServerProxy('http://localhost:1609/')
print("factorial of 5 is : %s" % str(proxy.find_factorial_rpc(5)))
print("factorial of 10 is : %s" % str(proxy.find_factorial_rpc(10)))
print("square of 10 is : %s" % str(proxy.find_square_rpc(10)))
#python
