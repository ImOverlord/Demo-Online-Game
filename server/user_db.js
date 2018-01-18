var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var userSchema = new Schema({
	_id : String,
	item_id : Number,
	username: { type: String, required: true, unique: true},
	password: { type: String, required: true},
	position_x : Number,
	position_y : Number,
	active : Number,
	direction : Number
});


var User = mongoose.model('User', userSchema);
module.exports = User;