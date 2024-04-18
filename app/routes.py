from flask import render_template
from flask import jsonify
from flask import Flask, request
from app import app
from serial_com import serial_read, serial_write

@app.route('/')
@app.route('/index')
def index():
    user = {'username': 'BobySandala'}
    posts = [
        {
            'Temperatura': '00.00',
            'Stare_Led': 'OFF'
        }
    ]
    return render_template('index.html', title='Home', user=user, posts=posts)

@app.route('/get_data')
def get_data():
    data = serial_read('d')
    temperature = 0
    led_state = -1
    inundatie_state = -1

    temperature = data.split(':')[0].strip()  # Extract temperature value after ':'
    led_state = data.split(':')[1].strip()  # Extract temperature value after ':'
    inundatie_state = data.split(':')[2].strip()  # Extract temperature value after ':'
    return jsonify({'temperature': temperature, 'led_state': led_state, 'inundatie_state': inundatie_state})
# You can now use the functions from serial_com module here

@app.route('/toggle_led')
def toggle_led():
    val = serial_write('a');
    return val
    
@app.route('/msg_send')
def msg_send():
    arg1 = request.args.get('arg1')  # Get the value of 'arg1' from the request
    print("Received arg1:", arg1)  # Print the value of arg1 for debugging
    val = serial_write(arg1)
    return 'Received arg1: {}'.format(arg1)