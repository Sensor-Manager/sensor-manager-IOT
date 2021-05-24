var http = require('http');
const fetch = require('node-fetch');
var obj = "";
//create a server object:
http.createServer(function (req, res) {
    var body = '';
    if (req.method == "POST") {
        console.log('POST /')

        req.on('data', function (data) {
            body += data;
            obj = data;
        });

        req.on('end', function () {
            console.log(body);
                obj = body;
        });



        console.log("here is the body" + obj)
        console.log(typeof(obj))
        let todo = {
            temp: obj,
            title: "loren impsum doloris",
            completed: false
        };

        fetch('https://grain-manager.herokuapp.com/editdata/0', {
            method: 'POST',
            body: obj,
            headers: { 'Content-Type': 'application/json' }
        }).then(res => res.json())
            .then(json => console.log(json));
        }


    var msg = createMessage();

    var jsonStr = JSON.stringify(msg);
    res.write(jsonStr); //write a response to the client
    res.end(); //end the response
}).listen(8080); //the server object listens on port 8080


function createMessage() {
    return {
        message: 'Hello World!',
        time: '2019-11-23 13:10:00'
    };
}
