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
		static public  var m_sprite:Sprite;

		// input
		//public var m_input:Input;

		// Keyboard
		var Key_Array:Array = new Array();

		// Physic
		public var m_world:b2World;
		public var m_iterations:int = 10;
		public var m_timeStep:Number = 1/10;

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

		//var m_sprite:Sprite;

		var test_ball:BBall;
		var test_blobby:BBlobby;
		var test_wall:BWall;
		var test_weaponGun:BWeaponGun;
		var test_weaponLaserGreen:BWeaponLaserGreen;
		var test_crate:BCrate;
		var test_palme:palme;
		
		

		// Fadenkreuz
		var f_kreuz:fadenkreuz;

		// Background
		var backGround:background;

		
		
		
		
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
			f_kreuz.x = event.stageX;
			f_kreuz.y = event.stageY;

			if (test_blobby!=null)
			{
				test_blobby.mouse_control("mouse_move",0,event.stageX,event.stageY);
				
				if (test_blobby.weapon!=null)
				{
					calc_mouse();
				}
			}
		}
		// MouseDown
		public function event_MouseDown(event:MouseEvent):void
		{
			if(test_blobby!=null)
			{
				test_blobby.mouse_control("mouse_down", 0, event.stageX, event.stageY);
			}
			
			trace(test_ball.body.GetCenterPosition().x + " " + test_ball.body.GetCenterPosition().y);
		}
		
		
		public function event_MouseUp(event:MouseEvent):void
		{
			if(test_blobby!=null)
			{
				test_blobby.mouse_control("mouse_up", 0, event.stageX, event.stageY);
			}
		}
		
		public function calc_mouse()
		{
			var a:int = f_kreuz.y - test_blobby.body.m_position.y + scrollY;
			var b:int = f_kreuz.x - test_blobby.body.m_position.x + scrollX;

			mouse_angle = Math.atan2(a,b);
			mouse_angle_vec = rad2vec(mouse_angle + test_blobby.body.m_rotation);
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

			// Keyboard
			for (var i:Number = 0; i < 255; i++)
			{
				Key_Array[i] = new BKey();
			}
			// Events
			addEventListener(Event.ENTER_FRAME, update, false, 0, true);
			//stage.addEventListener(MouseEvent.CLICK, click);

			m_sprite = new Sprite();




			loader.contentLoaderInfo.addEventListener( Event.COMPLETE, handleThumbSuccess );
			loader.contentLoaderInfo.addEventListener( IOErrorEvent.IO_ERROR, handleThumbError );
			loader.load( new URLRequest("test.png") );





			backGround = new background();
			addChild(backGround);



			// Creat world AABB
			var worldAABB:b2AABB = new b2AABB();
			worldAABB.minVertex.Set(-2000.0, -2000.0);
			worldAABB.maxVertex.Set(2000.0, 2000.0);

			var gravity:b2Vec2 = new b2Vec2(0.0, 400.0);
			var doSleep:Boolean = true;
			m_world = new b2World(worldAABB, gravity, doSleep);


			
			
			test_wall = new BWall(200,100, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
			
			test_wall = new BWall(150,200, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);

			test_wall = new BWall(200,400, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
			
			test_wall = new BWall(200,600, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
			
			test_wall = new BWall(200,800, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
		
			

			test_wall = new BWall(400,700, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
			
			test_wall = new BWall(600,700, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
			
			test_wall = new BWall(800,700, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
			
			test_wall = new BWall(1000,700, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
			
			
			
			test_wall = new BWall(1050,750, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
			
			test_wall = new BWall(1100,800, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
			
			test_wall = new BWall(1150,850, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
			
			test_wall = new BWall(1200,900, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
			
			test_wall = new BWall(1250,950, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
			
			test_wall = new BWall(1300,1000, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
			
			test_wall = new BWall(1400,1000, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
			
			test_wall = new BWall(1500,1000, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
			
			test_wall = new BWall(1600,1000, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
			
			test_wall = new BWall(1700,1000, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
			
			test_wall = new BWall(1800,1000, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
			
			
			test_wall = new BWall(1800,900, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
			
			test_wall = new BWall(1800,800, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
			
			test_wall = new BWall(1800,700, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
			
			test_wall = new BWall(1800,600, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
			
			test_wall = new BWall(1800,500, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
			
			test_wall = new BWall(1800,400, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);
			
			test_wall = new BWall(1800,300, 100, 100);
			test_wall.body=m_world.CreateBody(test_wall.bodyDef);
			addChild(test_wall.userData);

			
			


			test_crate = new BCrate(600,600);
			test_crate.body=m_world.CreateBody(test_crate.bodyDef);
			addChild(test_crate.userData);

			test_crate = new BCrate(600,550);
			test_crate.body=m_world.CreateBody(test_crate.bodyDef);
			addChild(test_crate.userData);
			
			test_crate = new BCrate(575,600);
			test_crate.body=m_world.CreateBody(test_crate.bodyDef);
			addChild(test_crate.userData);
			
			
			test_crate = new BCrate(1100,650);
			test_crate.body=m_world.CreateBody(test_crate.bodyDef);
			addChild(test_crate.userData);
			
			test_crate = new BCrate(1100,630);
			test_crate.body=m_world.CreateBody(test_crate.bodyDef);
			addChild(test_crate.userData);
			
			test_crate = new BCrate(1100,610);
			test_crate.body=m_world.CreateBody(test_crate.bodyDef);
			addChild(test_crate.userData);
			
			test_crate = new BCrate(1090,610);
			test_crate.body=m_world.CreateBody(test_crate.bodyDef);
			addChild(test_crate.userData);
			
	


			addChild(m_sprite);
			

			
			// player
			// Vars used to create bodies

			test_ball = new BBall(500, 50);
			test_ball.body=m_world.CreateBody(test_ball.bodyDef);
			addChild(test_ball.userData);

			test_blobby = new BBlobby(300,200);
			test_blobby.parent = this;
			test_blobby.body=m_world.CreateBody(test_blobby.bodyDef);
			addChild(test_blobby.userData);

			test_weaponGun = new BWeaponGun(750,600);
			test_weaponGun.body=m_world.CreateBody(test_weaponGun.bodyDef);
			addChild(test_weaponGun.userData);
			
			test_weaponLaserGreen = new BWeaponLaserGreen(240,265);
			test_weaponLaserGreen.body=m_world.CreateBody(test_weaponLaserGreen.bodyDef);
			addChild(test_weaponLaserGreen.userData);


			// Fadenkreuz
			f_kreuz = new fadenkreuz();
			addChild(f_kreuz);
			
			
			test_palme = new palme();
			addChild(test_palme);
			test_palme.x = 1050;
			test_palme.y = 310;
			
			
			
			// FPS-Counter
			m_fpsCounter.x = 7;
			m_fpsCounter.y = 5;
			addChildAt(m_fpsCounter, 42);

			
		}
		
		public function update(e:Event):void
		{
			updateNow = getTimer();
			var delta_T:uint = updateNow-updateLast;

			// clear for rendering
			m_sprite.graphics.clear();

			// Handle Input
			if (Key_Array[65].isPressed() == true || Key_Array[65].hasChanged() == true)
			{
				test_blobby.keyboard_control("left", Key_Array[65].pressed, Key_Array[65].time_pressedTotal);
			}
			if (Key_Array[68].isPressed() == true || Key_Array[68].hasChanged() == true)
			{
				test_blobby.keyboard_control("right", Key_Array[68].pressed, Key_Array[68].time_pressedTotal);
			}
			if (Key_Array[87].isPressed() == true || Key_Array[87].hasChanged() == true)
			{
				test_blobby.keyboard_control("up", Key_Array[87].pressed, Key_Array[87].time_pressedTotal);
			}
			if (Key_Array[83].isPressed() == true || Key_Array[83].hasChanged() == true)
			{
				test_blobby.keyboard_control("down", Key_Array[83].pressed, Key_Array[83].time_pressedTotal);
			}
			
			if (Key_Array[72].isPressed() == true || Key_Array[72].hasChanged() == true)
			{
				test_blobby.keyboard_control("drop", Key_Array[72].pressed, Key_Array[72].time_pressedTotal);
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
			if (test_blobby!=null)
			{
				calc_mouse();
				
				test_blobby.animation();
				test_blobby.action();
			}


			// Object Movement around Controller
			if (test_blobby!=null)
			{
				if (test_blobby.body.GetCenterPosition().x - scrollX >= 550)
				{
					scrollX = test_blobby.body.GetCenterPosition().x - 550;
				}
				else if (test_blobby.body.GetCenterPosition().x - scrollX <= 450)
				{
					scrollX = test_blobby.body.GetCenterPosition().x - 450;
				}
				if (test_blobby.body.GetCenterPosition().y - scrollY <= 250)
				{
					scrollY = test_blobby.body.GetCenterPosition().y - 250;
				}
				else if (test_blobby.body.GetCenterPosition().y - scrollY >= 350)
				{
					scrollY = test_blobby.body.GetCenterPosition().y - 350;
				}
			}
			
			// Update physics
			var physStart:uint = getTimer();
			m_world.Step(delta_T/1000, m_iterations);
			m_fpsCounter.updatePhys(physStart);

			/*if(test_blobby!=null)
			{
				if (test_blobby.weapon!=null)
				{
					test_blobby.weapon.m_rotation = mouse_angle + test_blobby.body.m_rotation;
				}
			}*/


			// collision
			for (var c:b2Contact = m_world.GetContactList(); c; c = c.GetNext())
			{
				if (c.GetManifoldCount() > 0)
				{
					var body1:b2Body = c.GetShape1().GetBody();
					var body2:b2Body = c.GetShape2().GetBody();

					if(body1 != null && body2 != null)
					{
						if(body1.GetUserData() != null && body2.GetUserData() != null)
						{
							if ((body1.GetUserData().type == "BWeaponGun" || body1.GetUserData().type == "BWeaponLaserGreen") && body2.GetUserData().type == "BBlobby")
							{
								body2.GetUserData().take_weapon(body1);
							}
							
							if ((body2.GetUserData().type == "BWeaponGun" || body2.GetUserData().type == "BWeaponLaserGreen")  && body1.GetUserData().type == "BBlobby")
							{
								body1.GetUserData().take_weapon(body2);
							}
							
							
							if (body1.GetUserData().type == "BMonitionGun" || body1.GetUserData().type == "BMonitionLaserGreen")
							{
								if(body1.GetUserData().userData != null)
									removeChild(body1.GetUserData().userData);
									
								body1.m_userData = null;
									
								m_world.DestroyBody(body1);
							}
							
							if (body2.GetUserData().type == "BMonitionGun" || body2.GetUserData().type == "BMonitionLaserGreen")
							{
								if(body1.GetUserData().userData != null)
									removeChild(body2.GetUserData().userData);
								
								body2.m_userData = null;
								
								m_world.DestroyBody(body2);
							}
						}
					}
				}
			}
			
			// grafik
			for (var bb:b2Body = m_world.m_bodyList; bb; bb = bb.m_next)
			{
				if (bb.m_userData != null)
				{
					// gravity master
					if (bb.m_userData.gravity_master != null)
					{
						if (bb.m_userData.gravity_master == true)
						{
							//bb.m_linearVelocity.y = - bb.m_mass * 40000;

							var tmp_v1:b2Vec2 = bb.GetCenterPosition();
							var tmp_v2:b2Vec2 = new b2Vec2(0, (-bb.m_mass * 400) * delta_T/1000);
							bb.WakeUp();
							bb.ApplyImpulse(tmp_v2, tmp_v1);
						}
					}
					
					// positionen updaten
					if (bb.m_userData.userData!=null)
					{
						bb.m_userData.userData.x = bb.m_position.x - scrollX;
						bb.m_userData.userData.y = bb.m_position.y - scrollY;
						bb.m_userData.userData.rotation = bb.m_rotation * (180/Math.PI);
						
						// items / waffen zeichnen
						if(bb.m_userData.type == "BBlobby")
						{
							bb.m_userData.draw_weapon();
						}
					}
				}

				// Umrandungen zeichnen
				/*for (var s:b2Shape = bb.GetShapeList(); s != null; s = s.GetNext())
				{
					DrawShape(s);
				}*/
			}
			// Joints zeichen
			/*for (var jj:b2Joint = m_world.m_jointList; jj; jj = jj.m_next)
			{
				DrawJoint(jj);
			}*/
			
			// Bilder
			test_palme.x = 1050 - scrollX;
			test_palme.y = 537 - scrollY;
			
			

			// update counter and limit framerate
			m_fpsCounter.update();
			//m_fpsCounter.updatePhys(updateLast);
			//FRateLimiter.limitFrame(50);

			// Delta Time
			updateLast = updateNow;
		}
		
		

		
		
		
		public function DrawShape(shape:b2Shape):void
		{
			var m_physScale:int;
			m_physScale=1;

			switch (shape.m_type)
			{
				case b2Shape.e_circleShape :
					{
						var circle:b2CircleShape = shape as b2CircleShape;
						var pos:b2Vec2 = circle.m_position;

						pos.x -= scrollX;
						pos.y -= scrollY;

						var r:Number = circle.m_radius;
						var k_segments:Number = 16.0;
						var k_increment:Number = 2.0 * Math.PI / k_segments;
						m_sprite.graphics.lineStyle(1,0xff0000,1);
						m_sprite.graphics.moveTo((pos.x + r) * m_physScale, (pos.y) * m_physScale);
						var theta:Number = 0.0;

						for (var i:int = 0; i < k_segments; ++i)
						{
							var d:b2Vec2 = new b2Vec2(r * Math.cos(theta), r * Math.sin(theta));
							var v:b2Vec2 = b2Math.AddVV(pos , d);
							m_sprite.graphics.lineTo((v.x) * m_physScale, (v.y) * m_physScale);
							theta += k_increment;
						}
						m_sprite.graphics.lineTo((pos.x + r) * m_physScale, (pos.y) * m_physScale);

						m_sprite.graphics.moveTo((pos.x) * m_physScale, (pos.y) * m_physScale);
						var ax:b2Vec2 = circle.m_R.col1;
						var pos2:b2Vec2 = new b2Vec2(pos.x + r * ax.x, pos.y + r * ax.y);
						m_sprite.graphics.lineTo((pos2.x) * m_physScale, (pos2.y) * m_physScale);

						pos.x += scrollX;
						pos.y += scrollY;

					};
					break;
				case b2Shape.e_polyShape :
					{
						var poly:b2PolyShape = shape as b2PolyShape;
						var tV:b2Vec2 = b2Math.AddVV(poly.m_position, b2Math.b2MulMV(poly.m_R, poly.m_vertices[i]));

						tV.x -= scrollX;
						tV.y -= scrollY;
						poly.m_position.x -= scrollX;
						poly.m_position.y -= scrollY;

						m_sprite.graphics.lineStyle(1,0xff0000,1);
						m_sprite.graphics.moveTo(tV.x * m_physScale, tV.y * m_physScale);

						for (i = 0; i < poly.m_vertexCount; ++i)
						{
							v = b2Math.AddVV(poly.m_position, b2Math.b2MulMV(poly.m_R, poly.m_vertices[i]));
							m_sprite.graphics.lineTo(v.x * m_physScale, v.y * m_physScale);
						}
						m_sprite.graphics.lineTo(tV.x * m_physScale, tV.y * m_physScale);

						tV.x += scrollX;
						tV.y += scrollY;
						poly.m_position.x += scrollX;
						poly.m_position.y += scrollY;

					};
					break;
			}
		}
		public function DrawJoint(joint:b2Joint):void
		{
			var m_physScale:int;
			m_physScale=1;

			var b1:b2Body = joint.m_body1;
			var b2:b2Body = joint.m_body2;

			b1.m_position.x  -= scrollX;
			b1.m_position.y  -= scrollY;
			b2.m_position.x  -= scrollX;
			b2.m_position.y  -= scrollY;

			var x1:b2Vec2 = b1.m_position;
			var x2:b2Vec2 = b2.m_position;
			var p1:b2Vec2 = joint.GetAnchor1();
			var p2:b2Vec2 = joint.GetAnchor2();

			m_sprite.graphics.lineStyle(1,0x44aaff,1/1);


			/*p1.x -= scrollX;
			p1.y -= scrollY;
			p2.x -= scrollX;
			p2.y -= scrollY;*/
			//x1.x -= scrollX;
			//x1.y -= scrollY;
			//x2.x -= scrollX;
			//x2.y -= scrollY;

			switch (joint.m_type)
			{
				case b2Joint.e_distanceJoint :
				case b2Joint.e_mouseJoint :
					m_sprite.graphics.moveTo(p1.x * m_physScale, p1.y * m_physScale);
					m_sprite.graphics.lineTo(p2.x * m_physScale, p2.y * m_physScale);
					break;

				case b2Joint.e_pulleyJoint :
					var pulley:b2PulleyJoint = joint as b2PulleyJoint;
					var s1:b2Vec2 = pulley.GetGroundPoint1();
					var s2:b2Vec2 = pulley.GetGroundPoint2();
					m_sprite.graphics.moveTo(s1.x * m_physScale, s1.y * m_physScale);
					m_sprite.graphics.lineTo(p1.x * m_physScale, p1.y * m_physScale);
					m_sprite.graphics.moveTo(s2.x * m_physScale, s2.y * m_physScale);
					m_sprite.graphics.lineTo(p2.x * m_physScale, p2.y * m_physScale);
					break;

				default :
					if (b1 == m_world.m_groundBody)
					{
						m_sprite.graphics.moveTo(p1.x * m_physScale, p1.y * m_physScale);
						m_sprite.graphics.lineTo(x2.x * m_physScale, x2.y * m_physScale);
					}
					else if (b2 == m_world.m_groundBody)
					{
						m_sprite.graphics.moveTo(p1.x * m_physScale, p1.y * m_physScale);
						m_sprite.graphics.lineTo(x1.x * m_physScale, x1.y * m_physScale);
					}
					else
					{
						m_sprite.graphics.moveTo(x1.x * m_physScale, x1.y * m_physScale);
						m_sprite.graphics.lineTo(p1.x * m_physScale, p1.y * m_physScale);
						m_sprite.graphics.lineTo(x2.x * m_physScale, x2.y * m_physScale);
						m_sprite.graphics.lineTo(p2.x * m_physScale, p2.y * m_physScale);
					}
			}
			b1.m_position.x  += scrollX;
			b1.m_position.y  += scrollY;
			b2.m_position.x  += scrollX;
			b2.m_position.y  += scrollY;
		}
	}
}