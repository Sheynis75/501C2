import requests

OGurl = "http://127.0.0.1:5000/"
Gtest = "https://httpbin.org/get"
Ptest = "https://httpbin.org/post"
sql = "http://127.0.0.1:5000/sqlcheck"
add = "http://127.0.0.1:5000/checkIn"
headers = {"User-Agent": "IWasBornInTheUSA"}
payload = {"authorize_code": "nuts",
           "agentId": "know",
           "IP": "127.0.0.14",
           "sleepTime": 33,
           "guido": "GUID goes here",
           "computerName": "StinkyMac",
           "DHkey": "Not Sure Yet"}


def get(url=sql, headers=headers):
    r = requests.get(url, headers=headers)
    print(r)
    print(r.text)


def post(url=add, deets=payload, headers=headers):
    r = requests.post(url, json=deets, headers=headers)
    print(r)
    print(r.text)


instructions = "\n\
Welcome to the client for the C2 server.\n\
Use the following commands to get started:\n\
only - post to database\n\
request {url}- run request test"


def mainLoop():
    running = True
    while(running):
        try:
            cmd = input("Type Cmd here:")
            if cmd == "help":
                print(instructions)
            elif (cmd == "exit"):
                print("See ya")
                running = False
            elif (cmd == "sql"):
                get(sql)
            elif (cmd == "add"):
                post(add)
            elif (cmd == "home"):
                post(OGurl)
            elif (cmd == "ptest"):
                post(Ptest)
            elif (cmd == "gtest"):
                get(Gtest)
            else:
                print("Error, I'm not really sure what you meant")
        except Exception as e:
            print(e)


if __name__ == '__main__':
    print(instructions)
    mainLoop()


# To implement later:

# command = input()
# match command.split():
#     case["quit"]:
#         quit()
#     case["load", filename]:
#         load_from(filename)
#     case["save", filename]:
#         save_to(filename)
#     case _:
#         print(f"Command '{command}' not understood")
