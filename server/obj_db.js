var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var objSchema = new Schema({
	_id : String,
	item_id: Number,
	position_x : Number,
	position_y : Number,
	vector_x : Number,
	vector_y : Number
});

var Obj = mongoose.model('Obj', objSchema);
module.exports = Obj;