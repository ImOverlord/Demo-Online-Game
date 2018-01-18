var express = require("express");
var app = express();
var myParser = require("body-parser");
var fs = require('fs')
var path = require('path');
var error_msg = "An Error occured: ";
var cors = require('cors');
var User = require('./user_db');
var Obj = require('./obj_db');
var mongoose = require("mongoose");
var timers = require("timers");
app.use(cors());
app.use(myParser.urlencoded({extended : true}));
app.set("port", process.env.PORT || 3000);
mongoose.connect('mongodb://localhost/online_game_alpha');
var id = 0;
var obj_id = 0;
app.listen(app.get('port'), "0.0.0.0", function() {
	console.log("Express Started");
	User.find({}, function(err, users) {
		if (err) throw err;

		for (i in users) {
			console.log(users[i].position_y);
			id += 1;
		}
	});
	Obj.find({}, function(err, object) {
		console.log(object);
		for (i in object) {
			object[i].remove(function(err) {
				if (err) throw err;
				console.log("Object Removed");
			})
		}
	})
});

app.post("/register", function(req, res) {

	var username1 = req.body.username;
	var password1 = req.body.password;

	User.find({username : username1}, function (err, docs) {
		if (docs.length){
			console.log('Name exists already');
			res.send("0");
		}else{
			id += 1
			var newUser = User({
				_id : id,
				item_id : 1,
				username : username1,
				password : password1,
				position_x : "100",
				position_y : "100",
				direction : "1",
				active : 1
			})
			newUser.save(function(err) {
				if (err) throw err;
				console.log('User created!');
				res.send("1")
			});
		}
	});
});

app.post("/login", function(req, res) {

	var username1 = req.body.username;
	var password1 = req.body.password;
	console.log("Login " + username1 + ":" + password1);

	User.find({username : username1}, function (err, docs) {
		if (docs.length){
			if (password1 == docs[0].password) {
				console.log(username1 + " logged in")
				docs[0].active = 1;
				docs[0].save(docs[0], function(error, user) {
					if(error) return next(error);
					
					res.send("1")
				});
			} else {
				console.log("Login Failed");
				res.send("0");
			}
		}else{
			console.log("User doesnt exist")
			res.send("0");
		}
	});
})

app.post("/disconnect", function(req, res) {

	var username1 = req.body.username;

	User.find({username : username1}, function (err, docs) {
		if (err) throw err;

		docs[0].active = 0;

		docs[0].save(docs[0], function(error, user) {
			if(error) return next(error);

			res.send("1");
		});
	});
})

app.get("/map", function(req, res) {

	User.find({}, function(err, users) {
		if (err) throw err;

		var string = "";
		for (i in users) {
			if (users[i].active == 1) {
				string += users[i].item_id + ":" + users[i].username + ":" + users[i].position_x + ":" + users[i].position_y + ":" + users[i].direction + ":\n";
			}
		}

		Obj.find({}, function(err, objects) {
			if (err) throw err;

			for (i in objects) {
				string += objects[i].item_id + ":" + "object" + ":" + objects[i].position_x + ":" + objects[i].position_y + ":\n";
			}
			res.send(string);
		})
	});
})

app.post("/my", function(req, res) {

	var username1 = req.body.username;
	User.find({username: username1}, function(err, users) {
		if (err) throw err;

		var string = users[0].item_id + ":" + users[0].username + ":" + users[0].position_x + ":" + users[0].position_y + ":" + users[0].direction + ":\n";
		console.log(string);
		res.send(string);
	})
})

function check_outofbound(new_pos_x, new_pos_y) {
	var map_x0 = 0;
	var map_xmax = 800;
	var map_y0 = 0;
	var map_ymax = 600;
	if (new_pos_x < map_x0) {
		new_pos_x = map_x0;
	}
	if (new_pos_x > map_xmax) {
		new_pos_x = map_xmax;
	}
	if (new_pos_y < map_y0) {
		new_pos_y = map_y0;
	}
	if (new_pos_y < map_ymax) {
		new_pos_y = map_ymax
	}
}

app.post("/move", function(req, res) {
	var username1 = req.body.username;
	var move = req.body.move;

	User.find({username : username1}, function (err, docs) {
		if (err) throw err;

		var new_pos_x = docs[0].position_x;
		var new_pos_y = docs[0].position_y;
		var new_direction = docs[0].direction;
		if (req.body.move == "1") {
			new_direction = 1;
			new_pos_y -= 10;
		}
		if (req.body.move == "2") {
			new_direction = 2;
			new_pos_y += 10;
		}
		if (req.body.move == "3") {
			new_direction = 3;
			new_pos_x -= 10;
		}
		if (req.body.move == "4") {
			new_direction = 4;
			new_pos_x += 10;
		}
		//Check for collision
		check_outofbound(new_pos_x, new_pos_y);
		console.log(username1 + " x:" + new_pos_x + " y:", new_pos_y);
		docs[0].position_x = new_pos_x;
		docs[0].position_y = new_pos_y;
		docs[0].direction = new_direction;
		docs[0].save(docs[0], function(error, user) {
			if(error) return next(error);
			
			res.send("1")
		});
	});
})

app.post('/shoot', function(req, res) {

	var username1 = req.body.username;
	var player_x = req.body.x;
	var player_y = req.body.y;
	if (req.body.direction == undefined) {
		var direction = req.body.direction;
	} else {
		var direction = req.body.direction;
	}

	console.log(username1 + " " + player_x + " " + player_y + " " + direction);
	var vector_x;
	var vector_y;
	if (direction == "1") {
		vector_y = -10;
		vector_x = 0;
	}
	if (direction == "2") {
		vector_y = 10;
		vector_x = 0;
	}
	if (direction == "3") {
		vector_y = 0;
		vector_x = -10;
	}
	if (direction == "4") {
		vector_y = 0;
		vector_x = 10;
	}
	var vector_y;
	obj_id += 1;
	var bullerObject = Obj({
		_id : obj_id,
		item_id : 2,
		position_x : player_x,
		position_y : player_y,
		vector_x : vector_x,
		vector_y : vector_y,
	})
	bullerObject.save(function(err) {
		if (err) throw err;
		res.send("1")
	});
})

process.on('SIGINT', function() {
	console.log("Caught interrupt signal");

	Obj.find({}, function(err, objects) {
		if (err) throw err;
		for (i in objects) {
			objects[i].remove(function(err) {
				if (err) throw err;
			})
		}
	});
	process.exit();
});

function bullet_outofbound(object) {

	if (object.position_x < 0 || object.position_x > 800) {
		return (1);
	} else if (object.position_y < 0 || object.position_y > 600) {
		return (1);
	} else {
		return (0);
	}
}

setInterval(function(){
	Obj.find({}, function(err, objects) {
		if (err) throw err;
		for (i in objects) {
			if (bullet_outofbound(objects[i]) == 1) {
				objects[i].remove(function(err) {
					if (err) throw err;
				})
			} else {
				objects[i].position_x += objects[i].vector_x;
				objects[i].position_y += objects[i].vector_y;
				objects[i].save(objects[i], function(error, user) {
					if(error) return next(error);
				});
			}
		}
	});
}, 100);