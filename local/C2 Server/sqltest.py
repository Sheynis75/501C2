import sqlite3

connection = sqlite3.connect("./data/real.db")
cursor = connection.cursor()

# cursor.execute('INSERT INTO Implants (authorize_code, agentId, checkTime, IP, sleepTime, guido, computerName, DHkey)\
#                 VALUES ("test", "Yardy", 34, "127.0.0.14", 36, "de", "ez", "nuts")')


connection.commit()

for row in cursor.execute("select * from Implants"):
    print(row)
