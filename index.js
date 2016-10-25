var express = require('express');
var app = express();
var port = 3000;
var mongoose = require('mongoose');
var path = 'mongodb://localhost/myapp';
var Schema = mongoose.Schema;
mongoose.connect(path);

var sensorSchema = new Schema({
	sensorName : String,
	sensorValue : Number
});

var sensor = mongoose.model('Sensor',sensorSchema);


 

app.get('/add',function(req,res,next){
	var sName = req.param('sName');
	var sValue = req.param('sValue');
	var lm35 = new sensor({
		sensorName : sName,
		sensorValue : sValue 
	});

	lm35.save(function(err){
		if (err)
		{
			console.log(err);
		}
		else{
			res.send('Inserted');
		}
	});
	
});


app.get('/drop',function(req,res,next){
	mongoose.connection.collections['sensors'].drop( function(err) {
		    res.send('collection dropped');

	} );
});

app.get('/getData',function(req,res,next){
	sensor.findOne({},{},{ sort : { '_id' : -1 } },function(err,data){
		res.json(data);
	});
});



app.listen(port, function(){
	console.log('Listening at port 3000');
});
