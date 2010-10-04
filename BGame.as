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


		// Frames
		static public  var m_fpsCounter:FpsCounter = new FpsCounter();
		public var m_FRateLimiter:FRateLimiter = new FRateLimiter();

		// time
		var updateNow:uint = getTimer();
		var updateLast:uint = getTimer();

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
		
		// canvas
		var canvasBD:BitmapData;
        var canvasBitmap:Bitmap;
	
		
		
		var mouse_angle:Number = 0;
		public var mouse_angle_vec:b2Vec2;

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

			if (level.player!=null)
			{
				level.player.mouse_control("mouse_move",0,event.stageX,event.stageY);
				
				if (level.player.weapon!=null)
				{
					calc_mouse();
				}
			}
		}
		// MouseDown
		public function event_MouseDown(event:MouseEvent):void
		{
			if(level.player!=null)
			{
				level.player.mouse_control("mouse_down", 0, event.stageX, event.stageY);
			}
		}
		
		
		public function event_MouseUp(event:MouseEvent):void
		{
			if(level.player!=null)
			{
				level.player.mouse_control("mouse_up", 0, event.stageX, event.stageY);
			}
		}
		
		public function calc_mouse()
		{
			var tmp_x:Number = level.player.body.GetPosition().x*config.phy_scaling + 20;
			var tmp_y:Number = level.player.body.GetPosition().y*config.phy_scaling + 23.5;
			
			var a:int = f_kreuz.y+7 - (tmp_y) + scrollY;
			var b:int = f_kreuz.x+7 - (tmp_x) + scrollX;

			mouse_angle = Math.atan2(a / config.phy_scaling, b / config.phy_scaling);
			mouse_angle_vec = rad2vec((mouse_angle) + level.player.body.GetAngle());
		}
		
		public function rad2vec(r:Number):b2Vec2
		{
			var tmp_v:b2Vec2 = new b2Vec2(Math.cos(r), Math.sin(r));
			return tmp_v;
		}
		
		public function handleThumbSuccess(e:Event):void
		{
			trace("fertig!");

			//testImg = new Bitmap(loader.content);



			testImgDT = new BitmapData(loader.width, loader.height);
			testImgDT.draw(loader.content);

			testImg = new Bitmap(testImgDT);
			testImg.x = -testImg.width/2;
			testImg.y = -testImg.height/2;
			//testImg.width = 100;
			//testImg.height = 100;
			testImg.smoothing = true;

			trace(testImg.width + " " + testImg.height);

			testMC.addChild(testImg);
		}
		public function handleThumbError(e:IOErrorEvent):void
		{
			trace("fehler!");
		}
		public function BGame()
		{
			// config
			config = new BConfig();
			
			// level
			level = new BLevel(this);
			level.load("huhu");
			
			// contactListener
			contactListener = new BContactListener();
			level.m_world.SetListener(contactListener);
			

			//init canvas and display bitmap for canvas
			canvasBD=new BitmapData(1000,600,false,0x000000);
			canvasBitmap=new Bitmap(canvasBD);
			
			addChild(canvasBitmap);
			
			
			addChild(level.m_sprite_debug);
			
			
			// Keyboard
			for (var i:Number = 0; i < 255; i++)
			{
				Key_Array[i] = new BKey();
			}
			// Events
			addEventListener(Event.ENTER_FRAME, update, false, 0, true);
			//stage.addEventListener(MouseEvent.CLICK, click);

			//m_sprite = new Sprite();
			//addChild(m_sprite);

			
			/*loader.contentLoaderInfo.addEventListener( Event.COMPLETE, handleThumbSuccess );
			loader.contentLoaderInfo.addEventListener( IOErrorEvent.IO_ERROR, handleThumbError );
			loader.load( new URLRequest("test.png") );*/

			
			// Fadenkreuz
			f_kreuz = new fadenkreuz();
			addChild(f_kreuz);			
			
			// FPS-Counter
			m_fpsCounter.x = 7;
			m_fpsCounter.y = 5;
			addChild(m_fpsCounter);
		}
		
		public function update(e:Event):void
		{
			updateNow = getTimer();
			var delta_T:uint = updateNow-updateLast;

			// clear for rendering
			//m_sprite.graphics.clear();

			// Handle Input
			if (Key_Array[65].isPressed() == true || Key_Array[65].hasChanged() == true)
			{
				level.player.keyboard_control("left", Key_Array[65].pressed, Key_Array[65].time_pressedTotal);
				/*var tmp_v1:b2Vec2 = new b2Vec2(test_ball.body.GetPosition().x, test_ball.body.GetPosition().y);
				var tmp_v2:b2Vec2 = new b2Vec2(-0.1,0);
				//test_blobby.body.WakeUp();
				test_ball.body.ApplyImpulse(tmp_v2, tmp_v1);*/
			
			}
			if (Key_Array[68].isPressed() == true || Key_Array[68].hasChanged() == true)
			{
				level.player.keyboard_control("right", Key_Array[68].pressed, Key_Array[68].time_pressedTotal);
			}
			if (Key_Array[87].isPressed() == true || Key_Array[87].hasChanged() == true)
			{
				level.player.keyboard_control("up", Key_Array[87].pressed, Key_Array[87].time_pressedTotal);
			}
			if (Key_Array[83].isPressed() == true || Key_Array[83].hasChanged() == true)
			{
				level.player.keyboard_control("down", Key_Array[83].pressed, Key_Array[83].time_pressedTotal);
			}
			
			if (Key_Array[72].isPressed() == true || Key_Array[72].hasChanged() == true)
			{
				level.player.keyboard_control("drop", Key_Array[72].pressed, Key_Array[72].time_pressedTotal);
			}
			
			if (Key_Array[Keyboard.ESCAPE].isPressed() == true)
			{
				removeEventListener(Event.ENTER_FRAME, update);

				var myParent:Main = parent as Main;
				myParent.stopGame();
			}
			if (Key_Array[Keyboard.ENTER].isPressed() == true)
			{
				//add_testObject();
				//test_blobby.weapon.change_carry_direction();
			}
			
			// Object animation
			if (level.player!=null)
			{
				calc_mouse();
				
				level.player.animation();
				level.player.action();
			}


			// Object Movement around Controller
			if (level.player!=null)
			{
				if ((level.player.body.GetPosition().x * config.phy_scaling) - scrollX >= 550)
				{
					scrollX = (level.player.body.GetPosition().x * config.phy_scaling) - 550;
				}
				else if ((level.player.body.GetPosition().x * config.phy_scaling) - scrollX <= 450)
				{
					scrollX = (level.player.body.GetPosition().x * config.phy_scaling) - 450;
				}
				if ((level.player.body.GetPosition().y * config.phy_scaling) - scrollY <= 250)
				{
					scrollY = (level.player.body.GetPosition().y * config.phy_scaling) - 250;
				}
				else if ((level.player.body.GetPosition().y * config.phy_scaling) - scrollY >= 350)
				{
					scrollY = (level.player.body.GetPosition().y * config.phy_scaling) - 350;
				}
			}
			
			
			
			// Update physics
			var physStart:uint = getTimer();
			level.m_world.Step(delta_T/1000, level.m_iterations);
			//level.m_world.Step(1/30, level.m_iterations);
			m_fpsCounter.updatePhys(physStart);
			
			
			// level destroy bodies
			level.destroy_body(true, null);

			
			
			// Background / Clear
			var playerRect:Rectangle = new Rectangle(0,0,1000,600);
			var playerPoint:Point=new Point(0,0);
			canvasBD.copyPixels(level.backGroundBD, playerRect, playerPoint);
			
			
			// grafik / rendering
			for (var bb:b2Body = level.m_world.m_bodyList; bb; bb = bb.m_next)
			{
				if (bb.m_userData != null)
				{
					// gravity master
					if (bb.m_userData.gravity_master != null)
					{
						if (bb.m_userData.gravity_master == true)
						{
							//bb.m_linearVelocity.y = - bb.m_mass * 40000;

							var tmp_v1:b2Vec2 = bb.GetPosition();
							var tmp_v2:b2Vec2 = new b2Vec2(0, (-bb.GetMass() * 40) * delta_T/1000);
							bb.WakeUp();
							bb.ApplyImpulse(tmp_v2, tmp_v1);
						}
					}
					
					
			
					
					// render
					if (bb.m_userData.userData!=null)
					{
						/*if(bb.m_userData.type=="BWeaponLaserGreen")
						{
							bb.m_userData.userData.x = (bb.GetPosition().x * config.phy_scaling) - scrollX;
							bb.m_userData.userData.y = (bb.GetPosition().y * config.phy_scaling) - scrollY;
							bb.m_userData.userData.rotation = bb.GetAngle() * (180/Math.PI);
						}
						else
						{
							bb.m_userData.userData.x = (bb.GetPosition().x * config.phy_scaling) - scrollX;
							bb.m_userData.userData.y = (bb.GetPosition().y * config.phy_scaling) - scrollY;
							bb.m_userData.userData.rotation = bb.GetAngle() * (180/Math.PI);
						}*/
						
						if(bb.m_userData.type=="BWall")
						{
							bb.m_userData.userData.x = (bb.GetPosition().x * config.phy_scaling) - scrollX;
							bb.m_userData.userData.y = (bb.GetPosition().y * config.phy_scaling) - scrollY;
							bb.m_userData.userData.rotation = bb.GetAngle() * (180/Math.PI);
						}
						else
						{
							bb.m_userData.bdraw();
						}
						
						
						// items / waffen zeichnen
						if(bb.m_userData.type == "BBlobby")
						{
							//trace(bb.m_userData.userData.x + " " + bb.m_userData.userData.y);
							
							bb.m_userData.draw_weapon();
						}
					}
				}
			}
			
			
			// Bilder
			for each (var img:BImage in level.images )
			{
				img.bdraw();
			}
			
			
			level.m_sprite_debug.x = 0 - scrollX;
			level.m_sprite_debug.y = 0 - scrollY;
			

			// update counter and limit framerate
			m_fpsCounter.update();
			//m_fpsCounter.updatePhys(updateLast);
			//FRateLimiter.limitFrame(50);

			// Delta Time
			updateLast = updateNow;
		}
	}
}