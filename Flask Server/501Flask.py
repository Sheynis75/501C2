from flask import Flask, send_file

app = Flask(__name__)

##@app.route('/')
##def download_file():
##    return send_file( 'README.md', as_attachment = True)
@app.route('/')
def test():
    return 'Test'
if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')
