# /*Develop an elementary catboat for any suitable customer interaction application.*/
import datetime
greetings = ['Hello!','Hi!']
salutations = ['Bye!','See you soon!','Have a good day!']
others = {"weather" : ["sunny","chilly","rainy"],
          "name" : ["My name is HarshBot","Myself HarshBot","People call me HarshBot"]
         }
def greet():
    print(random.choice(greetings))
def farewell():
    print(random.choice(salutations))
def date():
    print("The date is",str(datetime.datetime.now())[:10])
def time():
     print("The time is",str(datetime.datetime.now())[11:16])
def process(inp):
    if "hello" in inp.lower():
        greet()
    elif "bye" in inp.lower():
        farewell()
        return True
    elif "date" in inp.lower():
        date()
    elif "time" in inp.lower():
        time()
    else:
        found_response = False
        for key,value in others.items():
            if key in inp.lower():
                print(random.choice(value))
                found_response = True
                break
        if not found_response:
            print("idk")
            
    return False      

finished = False
while not finished:
    inp = input(">    ")
    finished = process(inp)