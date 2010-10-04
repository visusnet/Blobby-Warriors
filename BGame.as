package 
{
	// Flash
	import flash.events.Event;
	import flash.display.*;
	import flash.text.*;
	import flash.events.*;
	import flash.system.*;
	import flash.ui.*;
	import flash.utils.getTimer;
	import flash.display.MovieClip;
	import flash.net.URLRequest;
	import flash.geom.*;
	import flash.net.Socket;

	// Physic
	import Box2D.Dynamics.*;
	import Box2D.Collision.*;
	import Box2D.Collision.Shapes.*;
	import Box2D.Common.Math.*;
	import Box2D.Dynamics.Joints.*;
	import Box2D.Dynamics.Contacts.*;
	import Box2D.Dynamics.*;
	import Box2D.Common.*;
	import General.*;

	public class BGame extends MovieClip
	{
		// ### Atributes ###
		// main
		//static public  var m_sprite:Sprite;
		
		// config
		public var config:BConfig;

		// Keyboard
		var Key_Array:Array = new Array();

		// Testausgaben Textboxes
		var textBox_test:TextField;
		
		// socket
		var socket:Socket;
		var tmp_error_sock:String;
		
		// Frames
		static public  var m_fpsCounter:FpsCounter = new FpsCounter();
		public var m_FRateLimiter:FRateLimiter = new FRateLimiter();

		// time
		var updateNow:uint;
		var updateLast:uint;

		// scrolling
		var scrollX:int = 0;
		var scrollY:int = 0;

		// test-img
		var testImgDT:BitmapData;
		var testImg:Bitmap;
		var loader:Loader = new Loader();

		var testMC = new MovieClip();

		// Fadenkreuz
		var f_kreuz:fadenkreuz;

		var level:BLevel;
		var contactListener:BContactListener;
		var boundaryListener:BBoundaryListener;
		
		
		// canvas
		var canvasBD:BitmapData;
        var canvasBitmap:Bitmap;
	
		// Sprite own Debug
		var m_sprite_ownDebug:Sprite = new Sprite();
		
		// mouse
		var mouse_angle:Number = 0;
		public var mouse_angle_vec:b2Vec2;
		var mouse_angle_middle:Number = 0;
		
		
		// Leveleditor
		public var levelEditor:BLeveleditor;
		
		// PlayerLeiste
		var playerleiste:BPlayerLeiste;
		
		

		

		// KeyDown
		public function event_KeyDown(event:KeyboardEvent):void
		{
			Key_Array[event.keyCode].down();
		}
		// KeyUp
		public function event_KeyUp(event:KeyboardEvent):void
		{
			Key_Array[event.keyCode].up();
		}
		// MouseMove
		public function event_MouseMove(event:MouseEvent):void
		{
			f_kreuz.x = event.stageX - 7;
			f_kreuz.y = event.stageY - 7;

			if(levelEditor.status==false)
			{
				if (level.player!=null)
				{
					level.player.mouse_control("mouse_move",0,event.stageX,event.stageY);
					
					if (level.player.weapon!=null)
					{
						calc_mouse();
					}
				}
			}
			else
			{
				levelEditor.mouse_control("mouse_move",0,event.stageX,event.stageY);
			}
		}
		
		
		// MouseDown
		public function event_MouseDown(event:MouseEvent):void
		{
			if(levelEditor.status == true)
			{
				levelEditor.mouse_control("mouse_down", 0, event.stageX, event.stageY);
			}
			else if(level.player!=null)
			{
				level.player.mouse_control("mouse_down", 0, event.stageX, event.stageY);
			}
			
			
			
			
			/*var segment:b2Segment = new b2Segment();
			segment.p1 = level.player.body.GetPosition();
			segment.p2 = level.tmp_blobby.body.GetPosition();
			
			
			// get nearby shapes
			var aabb:b2AABB = new b2AABB();
			aabb.lowerBound.Set( (segment.p1.x, segment.p2.x) - 1, (segment.p1.y, segment.p2.y) - 1);
			aabb.upperBound.Set( (segment.p1.x, segment.p2.x) + 1, (segment.p1.y, segment.p2.y) + 1);
			var maxCount:int = 256;
			var shapes:Array = new Array(maxCount);
			var count:int = level.m_world.Query(aabb, shapes, maxCount);

			// impact point
			var lambda:Number = 1.0;
			var normal:b2Vec2 = new b2Vec2(0.0, 0.0);
			
			// for each shape...
			for (var i:int = 0; i < count; ++i)
			{
			  	// skip unhittable shapes
			   	/*if (shapes[i].IsSensor())
				  	continue;
			   	if ((shapes[i].GetFilterData().maskBits & mCategoryBits) == 0)
				  	continue;
			   	if ((shapes[i].GetFilterData().categoryBits & mMaskBits) == 0)
				  	continue;
			
			   	// get the parent body
			   	var body:b2Body = shapes[i].GetBody();
			   
			   
			   	// Debug-Output to see which Bodies/Shapes are in range
				if( body.GetUserData().type == "BBlobby")
					trace(getTimer() + " " + body.GetUserData().type + " " + body.GetUserData().health + " " + shapes[i].GetUserData());
				else
					trace(getTimer() + " " + body.GetUserData().type + " " + shapes[i].GetUserData());
			
		
			   	// ray-test
			   	if (!shapes[i].TestSegment(body.GetXForm(), new Array(lambda), normal, segment, lambda))
				  	continue;
			
			
			
				trace(getTimer() + " ray collide...");
			}*/
			
			
			
			

			// get nearby shapes
			/*var aabb:b2AABB;
			aabb.lowerBound.Set(0, 0);
			aabb.upperBound.Set(1, 1);
			var maxCount:int = 256;
			var shapes:Array = new Array(maxCount);
			var count:int = level.m_world.Query(aabb, shapes, maxCount);

			// impact point
			var lambda:Number = 1.0;
			var normal:b2Vec2 = new b2Vec2(level.player.GetPosition().x, level.player.GetPosition().x);
			
			// for each shape...
			for (var i:int = 0; i < count; ++i)
			{
			   // skip unhittable shapes
			   /*if (shapes[i].IsSensor())
				  continue;
			   if ((shapes[i].GetFilterData().maskBits & mCategoryBits) == 0)
				  continue;
			   if ((shapes[i].GetFilterData().categoryBits & mMaskBits) == 0)
				  continue;
			
			   // get the parent body
			   var body:b2Body = shapes[i].GetBody();
			
			   // ray-test
			   if (!shapes[i].TestSegment(body.GetXForm(), lambda, normal, segment, lambda))
				  continue;
			
				trace(getTimer() + " yo");
			   // ray collided with something...
			   // (do something here)
			}*/
			
			
			
			
			/*var s:b2Shape;
			
			for(s = level.player.body.GetShapeList(); s; s = s.GetNext())
			{
				if(s.m_userData == "body_oben")
				{
					
								
					if (s.TestSegment(body->GetXForm(), &lambda, &normal, segment, lambda))
						trace("yoooo");
					else
						trace("noooo");
					
				}
			}*/

			
			
			
			
			
			//level.destroy_body(false,level.player.body);
			
			
			//level.test_blobby.keyboard_control("right", true, 100);
			
			
			
			//scrollX += 100;
			//scrollY += 100;
			
			
			//trace(getTimer() + " " + level.test_groundline.body.GetPosition().x + " " + level.test_groundline.body.GetPosition().y);
			//trace(getTimer() + " " + level.test_blobby.body.GetPosition().x + " " + level.test_blobby.body.GetPosition().y);
			
			
			//if(level.player.groundBody_left!=null && level.player.groundBody_middle!=null && level.player.groundBody_right!=null)
			//	trace(getTimer() + " " + level.player.groundBody_left.GetUserData().m_angle + " " + level.player.groundBody_middle.GetUserData().m_angle + " " + level.player.groundBody_right.GetUserData().m_angle);
					
					
			/*trace("\n");
			
			if(level.player.groundBody_body_unten!=null)
				trace(getTimer() + "unten: " + level.player.groundBody_body_unten.GetUserData().m_angle * (180/Math.PI));
				
			if(level.player.groundBody_left!=null)
				trace(getTimer() + "left: " + level.player.groundBody_left.GetUserData().m_angle * (180/Math.PI));
				
			if(level.player.groundBody_middle!=null)
				trace(getTimer() + "middle: " + level.player.groundBody_middle.GetUserData().m_angle * (180/Math.PI));
				
			if(level.player.groundBody_right!=null)
				trace(getTimer() + "right: " + level.player.groundBody_right.GetUserData().m_angle * (180/Math.PI));
			*/
			
			
			/*trace("\n");
			
			if(level.player.groundBody_body_unten!=null)
				trace(getTimer() + "unten: " + level.player.groundBody_body_unten.GetUserData().type);
				
			if(level.player.groundBody_left!=null)
				trace(getTimer() + "left: " + level.player.groundBody_left.GetUserData().type);
				
			if(level.player.groundBody_middle!=null)
				trace(getTimer() + "middle: " + level.player.groundBody_middle.GetUserData().type);
				
			if(level.player.groundBody_right!=null)
				trace(getTimer() + "right: " + level.player.groundBody_right.GetUserData().type);
			*/
				
			//trace(getTimer() + " " + level.player.is_onGround());
			
					
			/*var s:b2Shape;
			
			for(s = level.player.body.GetShapeList(); s; s = s.GetNext())
			{
				if(s.m_userData == "ground_middle")
					s.GetContactList();
			}*/
		}
		
		
		public function event_MouseUp(event:MouseEvent):void
		{
			if(level!=null)
			{
				if(level.player!=null)
				{
					level.player.mouse_control("mouse_up", 0, event.stageX, event.stageY);
				}
			}
		}
		
		public function calc_mouse()
		{
			if(level.player==null)
			{
				this.m_sprite_ownDebug.graphics.clear();
				return;
			}
				
			if(level.player.weapon==null)
			{
				this.m_sprite_ownDebug.graphics.clear();
				return;
			}
			
			var tmp_carry_middle_x:int;
			if(level.player.GetDirection()==1)
				tmp_carry_middle_x = level.player.weapon.carry_middle_x_left;
			else
				tmp_carry_middle_x = level.player.weapon.carry_middle_x;
			
			var tmp_x:Number = (level.player.body.GetWorldCenter().x * config.phy_scaling) + tmp_carry_middle_x;
			var tmp_y:Number = (level.player.body.GetWorldCenter().y * config.phy_scaling) + level.player.weapon.carry_middle_y + level.player.weapon.getWeaponMovementFromCurFrame();
			
			var tmp_x_middle:Number = (level.player.body.GetWorldCenter().x * config.phy_scaling);
			var tmp_y_middle:Number = (level.player.body.GetWorldCenter().y * config.phy_scaling);
			
			
			
			// mouse angle right
			var a:int = f_kreuz.y - (tmp_y) + scrollY;
			var b:int = f_kreuz.x - (tmp_x) + scrollX;

			mouse_angle = Math.atan2(a / config.phy_scaling, b / config.phy_scaling);
			mouse_angle_vec = rad2vec((mouse_angle) + level.player.body.GetAngle());
			
			
			// mouse angle middle
			a = f_kreuz.y - (tmp_y_middle) + scrollY;
			b = f_kreuz.x - (tmp_x_middle) + scrollX;
			
			mouse_angle_middle = Math.atan2(a / config.phy_scaling, b / config.phy_scaling);
			
			
			
			this.m_sprite_ownDebug.graphics.clear();
			this.m_sprite_ownDebug.graphics.lineStyle(3, new b2Color(0,0,1).color, 1);
			this.m_sprite_ownDebug.graphics.moveTo(tmp_x-scrollX,tmp_y-scrollY);
			this.m_sprite_ownDebug.graphics.lineTo(f_kreuz.x,f_kreuz.y);
		}
		
		public function rad2vec(r:Number):b2Vec2
		{
			var tmp_v:b2Vec2 = new b2Vec2(Math.cos(r), Math.sin(r));
			return tmp_v;
		}
		

		
		public function unload_level()
		{
			// Events
			removeEventListener(Event.ENTER_FRAME, update);
			
			// MCs
			removeChild(level.m_sprite_debug);
		}
		
		public function load_level(level_name:String)
		{
			// Level
			level = new BLevel(this);
			level.load(level_name);
		}
		
		
		
		

		// SOCKET
		
		private function createSocket():void
		{
			socket = new Socket();
			socket.addEventListener("connect", socket_connect);
			socket.addEventListener("ioError", socket_ioError);
			//socket.addEventListener("error", socket_Error);
		}
		private function deleteSocket():void
		{
			socket.removeEventListener("connect",socket_connect);
			socket.removeEventListener("ioError", socket_ioError);
			//socket.removeEventListener("error", socket_Error);
			socket.close();
		}
		
		private function socket_connect(event:Event):void
		{
			trace("SOCKET: connected");
			
			socket.addEventListener(ProgressEvent.SOCKET_DATA, socketData);
			
			
			// create game if command comes
			//createGame();
		}
		
		private function socket_ioError(event:IOErrorEvent):void
		{
			trace("SOCKET: io error");
			trace(event);
			
			tmp_error_sock = event.toString();
			deleteSocket();
		}
		
		private function socket_Error(event:IOErrorEvent):void
		{
			trace("SOCKET: error");
			tmp_error_sock = event.toString();
			deleteSocket();
		}
		
		private function socketData(event:ProgressEvent):void
		{
		   	var msg:String = socket.readUTFBytes(socket.bytesAvailable);
		   	//trace(msg);
		   
		   	// PARSEN
		   	var array_packets:Array = msg.split("|");
			
			for each (var array_command:String in array_packets)
			{
				var array:Array = array_command.split(";");
				
				var type:String = String(array[0]);
				
				// object position
				if(type == "new_player")
				{
					var id:String = String(array[1]);
					var x:Number = Number(array[2]);
					var y:Number = Number(array[3]);
					//var name:Number = Number(array[4]);
					
					level.tmp_blobby = new BBlobby(this, x, y);
					level.tmp_blobby.id = id;
					level.tmp_blobby.add();
					
					var tmp_player:BPlayer = new BPlayer(level.tmp_blobby);
					level.player_array.push(tmp_player);
				}
				
				else if(type == "obj_pos")
				{
					var id:String = String(array[1]);
					var x:Number = Number(array[2]);
					var y:Number = Number(array[3]);
					var vx:Number = Number(array[4]);
					var vy:Number = Number(array[5]);
					var rot:Number = Number(array[6]);
				
					var bb:b2Body;
					for (bb = level.m_world.m_bodyList; bb; bb = bb.m_next)
					{
						if (bb.GetUserData() != null)
						{
							// richtiges object
							if (bb.GetUserData().type == "BBlobby")
							{
								if (bb.GetUserData().id == id)
								{
									bb.GetUserData().body.SetXForm(new b2Vec2(x,y), rot);
									bb.GetUserData().body.m_linearVelocity.x = vx;
									bb.GetUserData().body.m_linearVelocity.y = vy;
									bb.GetUserData().rotate_angle = rot * (180/Math.PI);
								}
							}
						}
					}
				}
			}

		
		}

		public function sendMessage(message:String):void
		{
		   if(socket && socket.connected)
		   {
			  socket.writeUTFBytes(message + "|\n");
			  socket.flush();
		   }
		}


		
		
		
		
		public function BGame(level:String)
		{
			// config
			config = new BConfig();
			
			createGame(level);
			
			// PlayerLeiste
			playerleiste = new BPlayerLeiste(this);
			playerleiste.show();
			
			
			// Server Verbindungsaufbau
			//
			//
			//createSocket();
			//socket.connect("paris079.server4you.de", 6881);
		}
		
		
		
		
		public function createGame(level:String)
		{
			// contactListener
			contactListener = new BContactListener();
			boundaryListener = new BBoundaryListener();
			
			//init canvas and display bitmap for canvas
			canvasBD=new BitmapData(config.dimension_x,config.dimension_y,false,0x000000);
			canvasBitmap=new Bitmap(canvasBD);
			addChild(canvasBitmap);
			
			// level
			load_level(level);
			
			// my debug sprite
			addChild(m_sprite_ownDebug);


			
			// Leveleditor
			levelEditor = new BLeveleditor(this);
			
			
			// textbox testausgaben
			textBox_test = new TextField();
			textBox_test.text = "...";
			textBox_test.x = 10;
			textBox_test.y = 100;
			textBox_test.width = 500;
			textBox_test.textColor = 0xff0000;
			
			addChild(textBox_test);
			
			
			
			// Keyboard
			for (var i:Number = 0; i < 255; i++)
			{
				Key_Array[i] = new BKey();
			}
			
			// Fadenkreuz
			f_kreuz = new fadenkreuz();
			addChild(f_kreuz);			
			
			// FPS-Counter
			m_fpsCounter.x = 7;
			m_fpsCounter.y = 5;
			addChild(m_fpsCounter);						
			
			// Leveleditor starten
			levelEditor.status = false;			
			
			// delta Time
			updateNow = getTimer();
			updateLast = getTimer();

			
		}
		
		
		
		public function update(e:Event):void
		{
			// deltaT Time
			updateNow = getTimer();
			var delta_T:uint = updateNow-updateLast;

			// Handle Input
			if (Key_Array[65].isPressed() == true || Key_Array[65].hasChanged() == true)
			{
				if(levelEditor.status==false)
					level.player.keyboard_control("left", Key_Array[65].pressed, Key_Array[65].time_pressedTotal);
			}
			if (Key_Array[68].isPressed() == true || Key_Array[68].hasChanged() == true)
			{
				if(levelEditor.status==false)
					level.player.keyboard_control("right", Key_Array[68].pressed, Key_Array[68].time_pressedTotal);
			}
			if (Key_Array[87].isPressed() == true || Key_Array[87].hasChanged() == true)
			{
				if(levelEditor.status==false)
				{
					level.player.keyboard_control("up", Key_Array[87].pressed, Key_Array[87].time_pressedTotal);
				}
			}
			if (Key_Array[83].isPressed() == true || Key_Array[83].hasChanged() == true)
			{
				if(levelEditor.status==false)
					level.player.keyboard_control("down", Key_Array[83].pressed, Key_Array[83].time_pressedTotal);
			}
			
			if (Key_Array[70].isPressed() == true || Key_Array[70].hasChanged() == true)
			{
				if(levelEditor.status==false)
					level.player.keyboard_control("drop", Key_Array[70].pressed, Key_Array[70].time_pressedTotal);
			}
			
			
			// arrow down
			if (Key_Array[40].isPressed() == true || Key_Array[40].hasChanged() == true)
			{
				if(levelEditor.status == true && Key_Array[40].time_pressedTotal < 100)
				{
					levelEditor.keyboard_control("down");
				}
			}
			
			// arrow up
			if (Key_Array[38].isPressed() == true || Key_Array[38].hasChanged() == true)
			{
				if(levelEditor.status == true && Key_Array[38].time_pressedTotal < 100)
				{
					levelEditor.keyboard_control("up");
				}
			}
			
			// arrow left
			if (Key_Array[37].isPressed() == true || Key_Array[37].hasChanged() == true)
			{
				if(levelEditor.status == true && Key_Array[37].time_pressedTotal < 100)
				{
					levelEditor.keyboard_control("left");
				}
			}
			
			// arrow right
			if (Key_Array[39].isPressed() == true || Key_Array[39].hasChanged() == true)
			{
				if(levelEditor.status == true && Key_Array[39].time_pressedTotal < 100)
				{
					levelEditor.keyboard_control("right");
				}
			}
			
			// DEL
			if (Key_Array[46].isPressed() == true || Key_Array[46].hasChanged() == true)
			{
				if(levelEditor.status == true && Key_Array[46].time_pressedTotal < 100)
				{
					levelEditor.keyboard_control("del");
				}
			}
			
			if (Key_Array[Keyboard.ESCAPE].isPressed() == true)
			{
				if(levelEditor.status == false)
				{
					unload_level();
	
					var myParent:Main = parent as Main;
					myParent.stopGame();
				}
				else if(Key_Array[Keyboard.ESCAPE].time_pressedTotal < 100)
				{
					levelEditor.keyboard_control("esc");
				}
			}
			if (Key_Array[Keyboard.ENTER].isPressed() == true && Key_Array[Keyboard.ENTER].time_pressedTotal < 100)
			{
				if(levelEditor.status == false)
				{
					// Leveleditor starten
					levelEditor.status = true;
					
					addChild(levelEditor.m_sprite);
					addChild(levelEditor.m_menu);
					removeChild(f_kreuz);
					
					Mouse.show();
				}
				else
				{
					// Leveleditor stoppen
					levelEditor.status = false;
					levelEditor.action = -1;
					
					removeChild(levelEditor.m_sprite);
					removeChild(levelEditor.m_menu);
					addChild(f_kreuz);
					
					Mouse.hide();
					
					//level.save();
				}
			}
			
			
			
			// Testausgaben
			if(level.player != null)
			{
				textBox_test.text = level.player.onGround + "\n";
				
				if(level.player.groundBody_body_unten!=null)
					textBox_test.appendText("unten: " + level.player.groundBody_body_unten.GetUserData().type + "\n");
					
				if(level.player.groundBody_left!=null)
				{
					textBox_test.appendText("left: " + level.player.groundBody_left.GetUserData().type);
					
					if(level.player.groundBody_left.GetUserData().type == "BGroundLine")
						textBox_test.appendText(level.player.groundBody_left.GetUserData().m_angle + "\n");
						
					textBox_test.appendText("\n");
				}
					
				if(level.player.groundBody_middle!=null)
				{
					textBox_test.appendText("middle: " + level.player.groundBody_middle.GetUserData().type);
					
					if(level.player.groundBody_middle.GetUserData().type == "BGroundLine")
						textBox_test.appendText(level.player.groundBody_middle.GetUserData().m_angle + "\n");
				
					textBox_test.appendText("\n");
				}
					
				if(level.player.groundBody_right!=null)
				{
					textBox_test.appendText("right: " + level.player.groundBody_right.GetUserData().type);
					
					if(level.player.groundBody_right.GetUserData().type == "BGroundLine")
						textBox_test.appendText(level.player.groundBody_right.GetUserData().m_angle + "\n");
				
					textBox_test.appendText("\n");
				}
				
					
				if(socket != null)
					textBox_test.appendText("Socket:" + socket.connected.toString() + "\n");
				else
					textBox_test.appendText("Socket: null " + tmp_error_sock + "\n");
			}
			

			
			
			// Level-Step
			if(levelEditor.status==false)
				level.logic();
			
			
			
			// Object animation
			if(levelEditor.status==false)
			{
				if (level.player!=null)
				{
					calc_mouse();
					
					if(level.player.weapon!=null)
					{
						level.player.weapon.angle = mouse_angle;
						level.player.weapon.angle_middle = mouse_angle_middle;
					}
				}
			}
			else
				if (level.player!=null)
					calc_mouse();
				

			// nur wenn Leveledit-Modus aus ist
			if(levelEditor.status==false)
			{
				// Object Movement around Controller
				if (level.player!=null)
				{
					if ((level.player.body.GetPosition().x * config.phy_scaling) - scrollX >= config.border_x1)
					{
						scrollX = (level.player.body.GetPosition().x * config.phy_scaling) - config.border_x1;
					}
					else if ((level.player.body.GetPosition().x * config.phy_scaling) - scrollX <= config.border_x2)
					{
						scrollX = (level.player.body.GetPosition().x * config.phy_scaling) - config.border_x2;
					}
					if ((level.player.body.GetPosition().y * config.phy_scaling) - scrollY <= config.border_y1)
					{
						scrollY = (level.player.body.GetPosition().y * config.phy_scaling) - config.border_y1;
					}
					else if ((level.player.body.GetPosition().y * config.phy_scaling) - scrollY >= config.border_y2)
					{
						scrollY = (level.player.body.GetPosition().y * config.phy_scaling) - config.border_y2;
					}
					
					
					// Begrenzung
					if(scrollX > 0 && (scrollX+config.border_x1+config.border_x2) > level.width)
						scrollX = level.width - (config.border_x1+config.border_x2);
						
					else if(scrollX < 0)
						scrollX = 0;
						
					
					// PLAYERLEISTE MIT BERÜCKSICHTIGEN!!
					if(scrollY > 0 && (scrollY + config.dimension_y) > level.height)
						scrollY = level.height -config.dimension_y;
					else if(scrollY < 0)
						scrollY = 0;
					
					// Debug Test
					textBox_test.appendText("Scrolling: " + scrollX + " " + scrollY);
				}
			}
			
			
			
			// Update physics
			var physStart:uint = getTimer();

			if(levelEditor.status == false)
				level.m_world.Step(delta_T/1000, level.m_iterations);
				//level.m_world.Step(1/30, level.m_iterations);
			else
				level.m_world.Step(0, level.m_iterations);

			m_fpsCounter.updatePhys(physStart);
			
			
			// level destroy bodies
			level.destroy_body(true, null);






			// network
			if(level.player != null)
			{
				var buf:String = "obj_pos" + ";" + level.player.body.GetUserData().id + ";";
				buf += level.player.body.GetPosition().x + ";" + level.player.body.GetPosition().y + ";";
				buf += level.player.body.m_linearVelocity.x + ";" + level.player.body.m_linearVelocity.y + ";";
				buf += level.player.body.GetAngle();
				sendMessage(buf);
			}






			
			// action / movement
			// nur wenn Leveledit-Modus aus ist
			var bb:b2Body;
			if(levelEditor.status==false)
			{
				for (bb = level.m_world.m_bodyList; bb; bb = bb.m_next)
				{
					if (bb.GetUserData() != null)
					{
						// gravity master
						if (bb.GetUserData().gravity_master != null)
						{
							if (bb.GetUserData().gravity_master == true)
							{
								var tmp_v1:b2Vec2 = bb.GetPosition();
								var tmp_v2:b2Vec2 = new b2Vec2(0, (-bb.GetMass() * level.gravity) * delta_T/1000);
								bb.WakeUp();
								bb.ApplyImpulse(tmp_v2, tmp_v1);
							}
						}
						
						
						// action
						if(bb.GetUserData().type == "BBlobby" || bb.GetUserData().type == "BBlobby1" || bb.GetUserData().type == "BMonitionGun" || bb.GetUserData().type == "BMonitionLaserGreen")
						{
							bb.GetUserData().action();
						}
						
						// animation
						if(bb.GetUserData().type == "BBlobby")
						{
							bb.GetUserData().animation();
						}
						
						// alive
						if(bb.GetUserData().type == "BThing" || bb.GetUserData().type == "BBlobby" || bb.GetUserData().type == "BCrate")
						{
							if(bb.GetUserData().health <= 0)
							{
								if(bb.GetUserData().type == "BCrate" ||
								   bb.GetUserData().type == "BThing")
									bb.GetUserData().destroy();
								
								level.destroy_body(false, bb);
								
								//bb.GetUserData().health = 100;
							}
						}
					}
				}
			}











			// clear
			canvasBD.fillRect(new Rectangle(0,0,config.dimension_x,config.dimension_y), 0x321e14);
			
			// Images Back-Layer
			var img:BImage;
			for each (img in level.images)
			{
				if(img.layer<0)
					img.bdraw();
			}
			
			// grafik / rendering
			for (bb = level.m_world.m_bodyList; bb; bb = bb.m_next)
			{
				if (bb.GetUserData() != null)
				{
					// render
					if (bb.GetUserData().userData!=null)
					{						
						bb.GetUserData().bdraw();
					}
				}
			}
			
			// items / waffen zeichnen
			for (bb = level.m_world.m_bodyList; bb; bb = bb.m_next)
			{
				if (bb.m_userData != null)
				{
					// items / waffen zeichnen
					if(bb.m_userData.type == "BBlobby")
					{
						bb.m_userData.draw_weapon();
					}
				}
			}
			
			// Images Front-Layer
			for each (img in level.images)
			{
				if(img.layer>0)
				{
					img.bdraw();
					
					//textBox_test.appendText("\n " + img.loader.contentLoaderInfo.bytesLoaded + " \ " + img.loader.contentLoaderInfo.bytesTotal);
					//trace("\n " + img.loader.contentLoaderInfo.bytesLoaded + " \ " + img.loader.contentLoaderInfo.bytesTotal);
					
				}
			}
			
			
			
			// Waypoints
			for each(var wayp:BWaypoint in level.waypoint_array)
			{
				this.m_sprite_ownDebug.graphics.lineStyle(5, new b2Color(0,0,1).color, 1);
				this.m_sprite_ownDebug.graphics.moveTo(wayp.posx-scrollX, wayp.posy-scrollY);
				this.m_sprite_ownDebug.graphics.lineTo(wayp.posx-scrollX+1, wayp.posy-scrollY+1);
				
				for each(var i:Array in wayp.connection)
				{
					var tmp_conn_wp:BWaypoint = level.get_waypoint(i[0]);
					
					this.m_sprite_ownDebug.graphics.lineStyle(1, new b2Color(0,0,1).color, 1);
					this.m_sprite_ownDebug.graphics.moveTo(wayp.posx-scrollX,wayp.posy-scrollY);
					this.m_sprite_ownDebug.graphics.lineTo(tmp_conn_wp.posx-scrollX, tmp_conn_wp.posy-scrollY);
				}
			}
			
			
			// Sprite Debug
			level.m_sprite_debug.x = 0 - scrollX;
			level.m_sprite_debug.y = 0 - scrollY;
			

			// update counter and limit framerate
			m_fpsCounter.update();
			//m_fpsCounter.updatePhys(updateLast);
			//FRateLimiter.limitFrame(30);

			// Delta Time
			updateLast = updateNow;
		}
	}
}