// -----------
// light_on
// -----------

Blockly.Blocks['get_yaw'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Get Yaw Degree");
    this.setOutput(true, null);
    this.setColour(315);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['get_yaw'] = function(block) {
  // TODO: Assemble JavaScript into code variable.
  var code = '...';
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.Blocks['get_tmp'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Get IMU Temperature");
    this.setOutput(true, null);
    this.setColour(240);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['get_tmp'] = function(block) {

  	var code3 =`get_tmp()`;
	code3 = 'window.parseFloat(' + code3 + ')';
	return [ code3 , Blockly.JavaScript.ORDER_NONE];
	
};



Blockly.Blocks['get_gyro'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Get Gyroscope")
        .appendField(new Blockly.FieldDropdown([["X","X"], ["Y","Y"], ["Z","Z"]]), "NAME")
        .appendField("Axis Data");
    this.setOutput(true, null);
    this.setColour(0);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['get_gyro'] = function(block) {
  var dropdown_name = block.getFieldValue('NAME');
   var droping;
    if(dropdown_name == "X"){
    droping = 0;
    }else if(dropdown_name == "Y"){
    droping = 1;
    }else{
    droping = 2;
    }   
   
   var code =`get_gyro(` +droping+ `)`;
  code = 'window.parseFloat(' + code + ')';
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.JavaScript.ORDER_NONE];
};




Blockly.Blocks['get_accel'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Get Accelerometer")
        .appendField(new Blockly.FieldDropdown([["X","X"], ["Y","Y"], ["Z","Z"]]), "NAME")
        .appendField("Axis Data");
    this.setOutput(true, null);
    this.setColour(120);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['get_accel'] = function(block) {
  var dropdown_name = block.getFieldValue('NAME');

    var droping;
    if(dropdown_name == "X"){
    droping = 0;
    }else if(dropdown_name == "Y"){
    droping = 1;
    }else{
    droping = 2;
    }   
   
   var code =`get_accel(` +droping+ `)`;
  code = 'window.parseFloat(' + code + ')';
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.JavaScript.ORDER_NONE];
};



Blockly.Blocks['buzzer_on_off'] = {
  init: function() {
    this.appendValueInput("NAME")
        .setCheck("Boolean")
        .appendField("Buzzer");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(290);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['buzzer_on_off'] = function(block) {
  var value_name = Blockly.JavaScript.valueToCode(block, 'NAME', Blockly.JavaScript.ORDER_ATOMIC);
  // TODO: Assemble JavaScript into code variable.

  if(value_name == "true"){
	  setting = 1;
  }else{
  setting = 0;
  }

  var code = 'buzzer_on_off('+setting+');\n';
  return code;
};




Blockly.Blocks['set_motor'] = {
  init: function() {
    this.appendValueInput("NAME")
        .setCheck("Number")
        .appendField("Set ")
        .appendField(new Blockly.FieldDropdown([["Front Left","Front Left"], ["Front Right","Front Right"], ["Rear Right","Rear Right"], ["Rear Left","Rear Left"]]), "NAME")
        .appendField("Motor speed to");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(285);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};


Blockly.JavaScript['set_motor'] = function(block) {
  var dropdown_name = block.getFieldValue('NAME');
  var value_name = Blockly.JavaScript.valueToCode(block, 'NAME', Blockly.JavaScript.ORDER_ATOMIC);
  
   var droping;
  if(dropdown_name == "Front Left"){
	  droping = 0;
  }else if(dropdown_name == "Front Right"){
	   droping = 1;
  }else if(dropdown_name == "Rear Right"){
	   droping = 2;
  }else{
	  droping = 3;
  }
  
  var code = 'set_motor('+droping+','+value_name+');\n';
  return code;
  
};


Blockly.Blocks['multiranger_y'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Get Multi Ranger Y-");
    this.setOutput(true, null);
    this.setColour(60);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['multiranger_y'] = function(block) {
  // TODO: Assemble JavaScript into code variable.
  var code =`multiranger_y()`;
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.JavaScript.ORDER_NONE];
};


Blockly.Blocks['multiranger_y1'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Get Multi Ranger Y+");
    this.setOutput(true, null);
    this.setColour(60);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['multiranger_y1'] = function(block) {
  // TODO: Assemble JavaScript into code variable.
 var code =`multiranger_y1()`;
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.JavaScript.ORDER_NONE];
};


Blockly.Blocks['multiranger_x'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Get Multi Ranger X-");
    this.setOutput(true, null);
    this.setColour(60);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['multiranger_x'] = function(block) {
  // TODO: Assemble JavaScript into code variable.
    var code =`multiranger_x()`;
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.JavaScript.ORDER_NONE];
};


Blockly.Blocks['multiranger_x1'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Get Multi Ranger X+");
    this.setOutput(true, null);
    this.setColour(60);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['multiranger_x1'] = function(block) {
  // TODO: Assemble JavaScript into code variable.
  var code =`multiranger_x1()`;
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.Blocks['buzzer'] = {
  init: function() {
    this.appendValueInput("NAME")
        .setCheck("Number")
        .appendField("Set Buzzer Frequecy");
    this.appendDummyInput()
        .appendField("Ms");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(285);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['buzzer'] = function(block) {
  var value_name = Blockly.JavaScript.valueToCode(block, 'NAME', Blockly.JavaScript.ORDER_ATOMIC);
   

  var code = '...;\n';
  return code;
};

Blockly.Blocks['bme280_h'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Get Humidity  ");
    this.setOutput(true, null);
    this.setColour(270);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['bme280_h'] = function(block) {
	
	var code =`bme280_h()`;
	code = 'window.parseFloat(' + code + ')';
	return [ code , Blockly.JavaScript.ORDER_NONE];
};

Blockly.Blocks['bme280_t'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Get Temperature ");
    this.setOutput(true, null);
    this.setColour(270);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['bme280_t'] = function(block) {
 	var code =`bme280_t()`;
	code = 'window.parseFloat(' + code + ')';
	return [ code , Blockly.JavaScript.ORDER_NONE];
};


Blockly.Blocks['bme280_p'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Get Pressure");
    this.setOutput(true, null);
    this.setColour(270);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['bme280_p'] = function(block) {
 	var code =`bme280_p()`;
	code = 'window.parseFloat(' + code + ')';
	return [ code , Blockly.JavaScript.ORDER_NONE];
};


Blockly.Blocks['optical_y'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Get Optical Motion Y");
    this.setOutput(true, null);
    this.setColour(180);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['optical_y'] = function(block) {
  // TODO: Assemble JavaScript into code variable.
   var code =`optical_y()`;
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.JavaScript.ORDER_NONE];
};


Blockly.Blocks['optical_x'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Get Optical Motion x");
    this.setOutput(true, null);
    this.setColour(180);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['optical_x'] = function(block) {
  // TODO: Assemble JavaScript into code variable.
  var code =`optical_x()`;
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.JavaScript.ORDER_NONE];
};


Blockly.Blocks['optical_alt'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Get Altitude");
    this.setOutput(true, null);
    this.setColour(180);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['optical_alt'] = function(block) {
  // TODO: Assemble JavaScript into code variable.
  
    var code =`read_altitude()`;
	code = 'window.parseFloat(' + code + ')';
	return [ code , Blockly.JavaScript.ORDER_NONE];
};



Blockly.Blocks['rgb_module'] = {
  init: function() {
    this.appendValueInput("ledNo")
        .setCheck("Number")
        .appendField("Led No");
    this.appendValueInput("red")
        .setCheck("Number")
        .appendField("RED");
    this.appendValueInput("green")
        .setCheck("Number")
        .appendField("GREEN");
    this.appendValueInput("blue")
        .setCheck("Number")
        .appendField("BLUE");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(180);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['rgb_module'] = function(block) {
  var value_ledno = Blockly.JavaScript.valueToCode(block, 'ledNo', Blockly.JavaScript.ORDER_ATOMIC);
  var value_red = Blockly.JavaScript.valueToCode(block, 'red', Blockly.JavaScript.ORDER_ATOMIC);
  var value_green = Blockly.JavaScript.valueToCode(block, 'green', Blockly.JavaScript.ORDER_ATOMIC);
  var value_blue = Blockly.JavaScript.valueToCode(block, 'blue', Blockly.JavaScript.ORDER_ATOMIC);
  // TODO: Assemble JavaScript into code variable.
  var code = 'rgbM('+value_ledno+', '+value_red+', '+value_green+', '+ value_blue +');\n';
  return code;
};





Blockly.Blocks['set_altitude'] = {
  init: function() {
    this.appendValueInput("NAME")
        .setCheck("Number")
        .appendField("Set Altitude");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(120);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['set_altitude'] = function(block) {
  var value_name = Blockly.JavaScript.valueToCode(block, 'NAME', Blockly.JavaScript.ORDER_ATOMIC);
  // TODO: Assemble JavaScript into code variable.
  var code = 'set_altitude('+value_name+');\n';
  return code;
};

Blockly.Blocks['thorttle'] = {
  init: function() {
    this.appendValueInput("NAME")
        .setCheck("Number")
        .appendField("Thorttle");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['thorttle'] = function(block) {
  var value_name = Blockly.JavaScript.valueToCode(block, 'NAME', Blockly.JavaScript.ORDER_ATOMIC);
  // TODO: Assemble JavaScript into code variable.
  var code = 'thorttle('+value_name+');\n';
  return code;
};

Blockly.Blocks['trim'] = {
  init: function() {
    this.appendValueInput("trimX")
        .setCheck("Number")
        .appendField("Trim X");
    this.appendValueInput("trimY")
        .setCheck("Number")
        .appendField("Trim Y");
    this.appendValueInput("trimZ")
        .setCheck("Number")
        .appendField("Trim Z");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(330);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};
Blockly.JavaScript['trim'] = function(block) {
  var value_trimx = Blockly.JavaScript.valueToCode(block, 'trimX', Blockly.JavaScript.ORDER_ATOMIC);
  var value_trimy = Blockly.JavaScript.valueToCode(block, 'trimY', Blockly.JavaScript.ORDER_ATOMIC);
  var value_trimz = Blockly.JavaScript.valueToCode(block, 'trimZ', Blockly.JavaScript.ORDER_ATOMIC);
  // TODO: Assemble JavaScript into code variable.
  var code = 'trim('+value_trimx+', '+value_trimy+', '+value_trimz+');\n';
  return code;
};


Blockly.Blocks['optical_flow_control'] = {
  init: function() {
    this.appendValueInput("NAME")
        .setCheck("Boolean")
        .appendField("Optical Flow Control");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(65);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['optical_flow_control'] = function(block) {
  var value_name = Blockly.JavaScript.valueToCode(block, 'NAME', Blockly.JavaScript.ORDER_ATOMIC);
  // TODO: Assemble JavaScript into code variable.
    var setting;
  if(value_name == "true"){
	  setting = 1;
  }else{
  setting = 0;
  }
  var code = 'optical_flow_control('+setting+');\n';
  //var code = '...;\n';
  return code;
};

Blockly.Blocks['altitude_control'] = {
  init: function() {
    this.appendValueInput("NAME")
        .setCheck(null)
        .appendField("Altitude Control");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(65);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['altitude_control'] = function(block) {
  var value_name = Blockly.JavaScript.valueToCode(block, 'NAME', Blockly.JavaScript.ORDER_ATOMIC);
  // TODO: Assemble JavaScript into code variable.
  var setting;
  if(value_name == "true"){
	  setting = 1;
  }else{
  setting = 0;
  }
  var code = 'altitude_control('+setting+');\n';
  //var code = '...;\n';
  return code;
};

Blockly.Blocks['yaw_control'] = {
  init: function() {
    this.appendValueInput("NAME")
        .setCheck("Boolean")
        .appendField("Yaw Control");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(65);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['yaw_control'] = function(block) {
  var value_name = Blockly.JavaScript.valueToCode(block, 'NAME', Blockly.JavaScript.ORDER_ATOMIC);
  // TODO: Assemble JavaScript into code variable.
   var setting;
  if(value_name == "true"){
	  setting = 1;
  }else{
  setting = 0;
  }
  var code = 'yaw_control('+setting+');\n';
  //var code = '...;\n';
  return code;
};

Blockly.Blocks['arm'] = {
  init: function() {
    this.appendValueInput("NAME")
        .setCheck("Boolean")
        .appendField("Arm Control");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(65);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['arm'] = function(block) {
  var value_name = Blockly.JavaScript.valueToCode(block, 'NAME', Blockly.JavaScript.ORDER_ATOMIC);
  // TODO: Assemble JavaScript into code variable.
  var setting;
  if(value_name == "true"){
	  setting = 1;
  }else{
  setting = 0;
  }
  var code = 'arm('+setting+');\n';
  //var code = '...;\n';
  return code;
};

Blockly.Blocks['take_off'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Take Off");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['take_off'] = function(block) {
  // TODO: Assemble JavaScript into code variable.
  var code ='take_off();\n';
  return code;
};

Blockly.Blocks['land'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Land");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['land'] = function(block) {
  // TODO: Assemble JavaScript into code variable.
  var code ='land();\n';
  return code;
};

Blockly.Blocks['go_forward'] = {
  init: function() {
    this.appendValueInput("NAME")
        .setCheck("Number")
        .appendField("Go Forward");
    this.appendDummyInput()
        .appendField(new Blockly.FieldDropdown([["s","s"], ["ms","ms"]]), "drop");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(330);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['go_forward'] = function(block) {
  var value_name = Blockly.JavaScript.valueToCode(block, 'NAME', Blockly.JavaScript.ORDER_ATOMIC);
  var dropdown_drop = block.getFieldValue('drop');
  // TODO: Assemble JavaScript into code variable.
  //drop = drop ? drop.toString() : '';
  
  var droping;
  if(dropdown_drop == "s"){
	  droping = 1;
	  value_name = value_name*1000;
  }else if(dropdown_drop == "ms"){
	   droping = 2;
  }
    var code = 'go_forward('+value_name+', '+droping+');\n';
   //var code = 'go_forward('+value_name+');\n';
  return code;
};

Blockly.Blocks['go_back'] = {
  init: function() {
    this.appendValueInput("NAME")
        .setCheck("Number")
        .appendField("Go Back");
    this.appendDummyInput()
        .appendField(new Blockly.FieldDropdown([["s","s"], ["ms","ms"]]), "drop");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(330);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['go_back'] = function(block) {
  var value_name = Blockly.JavaScript.valueToCode(block, 'NAME', Blockly.JavaScript.ORDER_ATOMIC);
  var dropdown_drop = block.getFieldValue('drop');
  // TODO: Assemble JavaScript into code variable.
  var droping;
  if(dropdown_drop == "s"){
	  droping = 1;
	  value_name = value_name*1000;
  }else if(dropdown_drop == "ms"){
	   droping = 2;
  }
  var code = 'go_back('+value_name+', '+droping+');\n';
  return code;
};

Blockly.Blocks['go_left'] = {
  init: function() {
    this.appendValueInput("NAME")
        .setCheck("Number")
        .appendField("Go Left");
    this.appendDummyInput()
        .appendField(new Blockly.FieldDropdown([["s","s"], ["ms","ms"]]), "drop");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(330);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};
Blockly.JavaScript['go_left'] = function(block) {
  var value_name = Blockly.JavaScript.valueToCode(block, 'NAME', Blockly.JavaScript.ORDER_ATOMIC);
  var dropdown_drop = block.getFieldValue('drop');
  // TODO: Assemble JavaScript into code variable.
   var droping;
  if(dropdown_drop == "s"){
	  droping = 1;
	  value_name = value_name*1000;
  }else if(dropdown_drop == "ms"){
	   droping = 2;
  }
  var code = 'go_left('+value_name+', '+droping+');\n';
  return code;
};

Blockly.Blocks['go_right'] = {
  init: function() {
    this.appendValueInput("NAME")
        .setCheck("Number")
        .appendField("Go Right");
    this.appendDummyInput()
        .appendField(new Blockly.FieldDropdown([["s","s"], ["ms","ms"]]), "drop");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(330);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['go_right'] = function(block) {
  var value_name = Blockly.JavaScript.valueToCode(block, 'NAME', Blockly.JavaScript.ORDER_ATOMIC);
  var dropdown_drop = block.getFieldValue('drop');
  // TODO: Assemble JavaScript into code variable.
   var droping;
  if(dropdown_drop == "s"){
	  droping = 1;
	  value_name = value_name*1000;
  }else if(dropdown_drop == "ms"){
	   droping = 2;
  }
  var code = 'go_right('+value_name+', '+droping+');\n';
  return code;
};

Blockly.Blocks['yaw_right'] = {
  init: function() {
    this.appendValueInput("NAME")
        .setCheck("Number")
        .appendField("Yaw Right");
    this.appendDummyInput()
        .appendField("Degrees");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(60);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['yaw_right'] = function(block) {
  var value_name = Blockly.JavaScript.valueToCode(block, 'NAME', Blockly.JavaScript.ORDER_ATOMIC);
  // TODO: Assemble JavaScript into code variable.
  var code = 'yaw_right('+value_name+');\n';
  return code;
};


Blockly.Blocks['yaw_left'] = {
  init: function() {
    this.appendValueInput("NAME")
        .setCheck("Number")
        .appendField("Yaw Left");
    this.appendDummyInput()
        .appendField("Degrees");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(60);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['yaw_left'] = function(block) {
  var value_name = Blockly.JavaScript.valueToCode(block, 'NAME', Blockly.JavaScript.ORDER_ATOMIC);
  // TODO: Assemble JavaScript into code variable.
   var code = 'yaw_left('+value_name+');\n';
  return code;
};

Blockly.Blocks['set_led'] = {
  init: function() {
    this.appendValueInput("NAME")
        .setCheck("Boolean")
        .appendField("Set ")
        .appendField(new Blockly.FieldDropdown([["red","red"], ["green","green"], ["blue","blue"]]), "NAME")
        .appendField(" Led To");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(210);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};
Blockly.JavaScript['set_led'] = function(block) {
  var dropdown_name = block.getFieldValue('NAME');
  var value_name = Blockly.JavaScript.valueToCode(block, 'NAME', Blockly.JavaScript.ORDER_ATOMIC);
  // TODO: Assemble JavaScript into code variable.
  var droping;
  if(dropdown_name == "red"){
	  droping = 0;
  }else if(dropdown_name == "green"){
	   droping = 1;
  }else{
	  droping = 2;
  }
  var setting;
  
  if(value_name == "true"){
	  setting = 1;
  }else{
  setting = 0;
  }

  
  var code = 'set_led('+droping+','+setting+');\n';
  return code;
};

Blockly.Blocks['read_battery'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Read Battery Voltage");
    this.setOutput(true, null);
    this.setColour(210);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['read_battery'] = function(block) {
  // TODO: Assemble JavaScript into code variable.
	// var code3 = 'set_battert()';
	var code3 =`set_battert()`;
	code3 = 'window.parseFloat(' + code3 + ')';
	return [ code3 , Blockly.JavaScript.ORDER_NONE];
};



Blockly.Blocks['debug'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Debug");
    this.setOutput(true, null);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.JavaScript['debug'] = function(block) {
  // TODO: Assemble JavaScript into code variable.
	var code =`debug()`;
	//code = 'window.parseFloat(' + code3 + ')';
	return [ code , Blockly.JavaScript.ORDER_NONE];
};





