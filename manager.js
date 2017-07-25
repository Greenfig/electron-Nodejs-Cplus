// Imports
const addon = require('./build/Release/addon');
// Classes
module.exports = {
    fact: function Factoral(number){
        this.number = number;
        this.answer;
        this.calcFactoral = function (){
            this.answer = addon.factoral(parseInt(this.number));
        };
        this.getValue = function(){
            return this.answer;
        }
    }
}
