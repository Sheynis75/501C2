from flask import Flask, send_file, request, jsonify

app = Flask(__name__)

##@app.route('/')
##def download_file():
##    return send_file( 'README.md', as_attachment = True)
@app.route('/')
def test():
    headers = request.headers
    auth = headers.get("ch0nk")
    if auth == 'lol':
        
        #return jsonify({"message": "OK: Authorized"}), 200
        return "Yay"
    else:
        return jsonify({"message": "ERROR: Unauthorized"}), 401
if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')
