from flask import Flask, send_file, request, jsonify

app = Flask(__name__)

##@app.route('/')
##def download_file():
##    return send_file( 'README.md', as_attachment = True)
@app.route('/', methods=['GET'])
def test():
    headers = request.headers
    auth = headers.get("ch0nk")
    if auth == 'lol':
        #return jsonify({"message": "OK: Authorized"}), 200
        return "Yay"
    else:
        return "hi", 401

@app.route('/', methods=['POST'])
def index():
    body = request.data.decode("utf-8") 
    print(body)
    if body: 
        return "Got it"
    else:
        return "WHAT?", 401
if __name__ == '__main__':
    app.run(debug=True)
