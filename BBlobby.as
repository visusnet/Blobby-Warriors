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
	
	public class BBlobby
	{
		// ### Atributes ###
		public var parent:BGame;
		
		public var userData:object_blobby;
		
		public var bodyDef:b2BodyDef;
		public var body:b2Body;
		
		var circleDef_oben = new b2CircleDef();
		var circleDef_unten = new b2CircleDef();
		var circleDef_ground1 = new b2CircleDef();
		var circleDef_ground2 = new b2CircleDef();
		var circleDef_ground3 = new b2CircleDef();
		var circleDef_left1 = new b2CircleDef();
		var circleDef_right1 = new b2CircleDef();
			
		private var speed_vert:Number;
		private var speed_hori:Number;
		
		private var jump:int;
		
		private var frame_cur:int;
		private var frame_max:int;
		private var frame_hz:int;
		private var frame_time_last:uint;
		
		private var onGround:Boolean=false;
		private var onLeft:Boolean=false;
		private var onRight:Boolean=false;
		
		private var move_walk:Boolean;
		
		private var rotate_angle:int;
		private var rotate:Boolean;
		private var rotate_hz:int;
		private var rotate_time_last:uint;
		private var rotate_direction:int;
		
		private var direction:int;
		
		var weapon:*;
		
		var mouse_down:Boolean;
		
		
		public var gravity_master:Boolean = false;
		
		public var type:String = "BBlobby";

		public function add()
		{
			body=parent.level.m_world.CreateDynamicBody(bodyDef);
			parent.addChild(userData);
			
			body.CreateShape(circleDef_oben);
			body.CreateShape(circleDef_unten);
			/*body.CreateShape(circleDef_ground1);
			body.CreateShape(circleDef_ground2);
			body.CreateShape(circleDef_ground3);
			/*body.CreateShape(circleDef_left1);
			body.CreateShape(circleDef_right1);*/
			
			//body.SetMassFromShapes();
			
			/*var tmp_mass:b2MassData = new b2MassData();
			tmp_mass.mass = 20;
			body.SetMass(tmp_mass);*/
			
			var tmp_mass:b2MassData = new b2MassData();
			tmp_mass.mass = 20;
			tmp_mass.I = 3;
			tmp_mass.center.SetZero();
			body.SetMass(tmp_mass);
		}
		
		public function bdraw()
		{
			var trans_x:Number = 19;
			var trans_y:Number = 22;
			var trans_x2:Number = 19/2;
			var trans_y2:Number = 22/2;
			
			var angle_in_radians = body.GetAngle();
			
			var rotationMatrix:Matrix = new Matrix();
			rotationMatrix.translate(-trans_x,-trans_y);
			rotationMatrix.rotate(angle_in_radians);
			rotationMatrix.translate(trans_x,trans_y);
			
			rotationMatrix.tx += trans_x2;
			rotationMatrix.ty += trans_y2;
			
			var matrixImage:BitmapData = new BitmapData(60, 60, true, 0x00000000);
			matrixImage.draw(userData, rotationMatrix);
		
			var playerRect:Rectangle = new Rectangle(0,0,60,60);
			var playerPoint:Point=new Point(((body.GetPosition().x-(trans_x+trans_x2)/parent.config.phy_scaling) * parent.config.phy_scaling) - parent.scrollX,((body.GetPosition().y-(trans_y+trans_y2)/parent.config.phy_scaling) * parent.config.phy_scaling) - parent.scrollY);
			parent.canvasBD.copyPixels(matrixImage, playerRect, playerPoint);
		}
		
		public function BBlobby(p:BGame, x:int, y:int)
		{
			parent = p;
			var phy_scale:Number = parent.config.phy_scaling;
			
			speed_vert = 250 / parent.config.phy_scaling;
			speed_hori = 200 / parent.config.phy_scaling;
			
			jump = 0;
			
			frame_cur = 1;
			frame_max = 8;
			frame_hz = 50;
			frame_time_last = 0;
			
			move_walk = false;
			
			rotate_angle = 0;
			rotate = false;
			rotate_hz = 5;
			rotate_time_last = 0;
			
			direction = 1;
			
			bodyDef = new b2BodyDef();
			circleDef_oben = new b2CircleDef();
			circleDef_unten = new b2CircleDef();
			circleDef_ground1 = new b2CircleDef();
			circleDef_ground2 = new b2CircleDef();
			circleDef_ground3 = new b2CircleDef();
			circleDef_left1 = new b2CircleDef();
			circleDef_right1 = new b2CircleDef();
			
			
			circleDef_oben.radius = 13 / phy_scale;
			circleDef_oben.density = 1;
			circleDef_oben.friction = 0.5;
			circleDef_oben.restitution = 0.6;
			circleDef_oben.localPosition.Set(1 / phy_scale, -9 / phy_scale);
			circleDef_oben.userData = "body_oben";
			circleDef_oben.categoryBits = 0x0004;
	
			circleDef_unten.radius = 17 / phy_scale;
			circleDef_unten.density = 0.6;
			circleDef_unten.friction = 1;
			circleDef_unten.restitution = 0.0;
			circleDef_unten.localPosition.Set(1 / phy_scale, 7 / phy_scale);
			circleDef_unten.userData = "ground"; 
			circleDef_unten.categoryBits = 0x0004;
			
			
			circleDef_ground1.radius = 12 / phy_scale;
			circleDef_ground1.density = 0;
			circleDef_ground1.friction = 1;
			circleDef_ground1.restitution = 0.0;
			circleDef_ground1.localPosition.Set(1 / phy_scale, 12 / phy_scale);
			circleDef_ground1.userData = "ground"; 
			circleDef_ground1.categoryBits = 0x0004;

			
			circleDef_ground2.radius = 10 / phy_scale;
			circleDef_ground2.density = 0;
			circleDef_ground2.friction = 0;
			circleDef_ground2.restitution = 0.0;
			circleDef_ground2.localPosition.Set(-5 / phy_scale, 10 / phy_scale);
			circleDef_ground2.userData = "ground"; 
			circleDef_ground2.categoryBits = 0x0004;
			//bodyDef.AddShape(circleDef_ground2);
			
			circleDef_ground3.radius = 10 / phy_scale;
			circleDef_ground3.density = 0;
			circleDef_ground3.friction = 0;
			circleDef_ground3.restitution = 0.0;
			circleDef_ground3.localPosition.Set(6 / phy_scale, 10 / phy_scale);
			circleDef_ground3.userData = "ground"; 
			circleDef_ground3.categoryBits = 0x0004;
			//bodyDef.AddShape(circleDef_ground3);
			
			circleDef_left1.radius = 5 / phy_scale;
			circleDef_left1.density = 0;
			circleDef_left1.friction = 1;
			circleDef_left1.restitution = 0.0;
			circleDef_left1.localPosition.Set(-13 / phy_scale, 0 / phy_scale);
			circleDef_left1.userData = "left"; 
			circleDef_left1.categoryBits = 0x0004;
			circleDef_left1.maskBits = 0x0001;
			//bodyDef.AddShape(circleDef_left1);
			
			circleDef_right1.radius = 5 / phy_scale;
			circleDef_right1.density = 0;
			circleDef_right1.friction = 1;
			circleDef_right1.restitution = 0.0;
			circleDef_right1.localPosition.Set(13 / phy_scale, 0 / phy_scale);
			circleDef_right1.userData = "right"; 
			circleDef_right1.categoryBits = 0x0004;
			circleDef_right1.maskBits = 0x0001;
			//bodyDef.AddShape(circleDef_right1);
			
			

			


			userData = new object_blobby();

			bodyDef.userData = this;
			bodyDef.position.x = x / phy_scale;
			bodyDef.position.y = y / phy_scale;
			
			bodyDef.fixedRotation=true;
		}
		
		public function draw_weapon()
		{
			if(weapon != null)
			{
				weapon.userData.x = ((body.GetWorldCenter().x + weapon.blobbyX_draw/parent.config.phy_scaling) * parent.config.phy_scaling) - parent.scrollX;
				weapon.userData.y = ((body.GetWorldCenter().y + weapon.blobbyY_draw/parent.config.phy_scaling) * parent.config.phy_scaling) -  parent.scrollY;
				weapon.userData.rotation = ( parent.mouse_angle * (180/Math.PI)) + (body.GetAngle() * (180/Math.PI));
				
				/*var tmp:b2Vec2 = rotateMC(weapon.userData, (mouse_angle * (180/Math.PI)), weapon.blobbyX_rotate, weapon.blobbyY_rotate);
			

				weapon.userData.rotation = mouse_angle * (180/Math.PI);
				weapon.userData.x -= tmp.x;
				weapon.userData.y -= tmp.y;*/
			}
		}
		
		/*private function rotateMC(clip_mc:MovieClip, rotation_number:Number, virtualX_number:int, virtualY_number:int):b2Vec2
		{
			//clip_mc       - der zu drehende Clip
			//rotation_number   - der Wert, der zur aktuellen Rotation addiert wird
			//virtualX_number   - x-Position des virtuellen Drehpunkts (im Koordinatensystem des Zielclips)
			//virtualY_number   - y-Position des virtuellen Drehpunkts (im Koordinatensystem des Zielclips)
			//1. virtuellen Drehpunkt vor Rotation sichern
			var oldVirtualX_number = clip_mc.x + Math.cos(clip_mc.rotation * Math.PI / 180) * virtualX_number - Math.sin(clip_mc.rotation * Math.PI / 180) * virtualY_number;
			var oldVirtualY_number = clip_mc.y + Math.sin(clip_mc.rotation * Math.PI / 180) * virtualX_number + Math.cos(clip_mc.rotation * Math.PI / 180) * virtualY_number;
		
			//2. Zielclip drehen
			//clip_mc.rotation = rotation_number;
		
			//3. resultierende Position des virtuellen Drehpunkts ausrechnen
			var newVirtualX_number = clip_mc.x + Math.cos(clip_mc.rotation * Math.PI / 180) * virtualX_number - Math.sin(clip_mc.rotation * Math.PI / 180) * virtualY_number;
			var newVirtualY_number = clip_mc.y + Math.sin(clip_mc.rotation * Math.PI / 180) * virtualX_number + Math.cos(clip_mc.rotation * Math.PI / 180) * virtualY_number;
		
			//Tatsaechlichen Drehpunkt dementsprechend verschieben
			//clip_mc.x -= newVirtualX_number - oldVirtualX_number;
			//clip_mc.y -= newVirtualY_number - oldVirtualY_number;
		
			return new b2Vec2(newVirtualX_number - oldVirtualX_number, newVirtualY_number - oldVirtualY_number);
			
			//Zum testen, den virtuellen Punkt sichtbar machen
			/*this.attachMovie("test", "test2", 1);
			this["test2"]._x = oldVirtualX_number;
			this["test2"]._y = oldVirtualY_number;
		}*/
		
		public function drop_weapon()
		{
			if(weapon!=null)
			{
				weapon.create(0,0,false);
				
				//weapon.body.SetXForm(new b2Vec2(0.1,0.1) , 0);
				
				weapon.add();
				
				//weapon.body = parent.level.m_world.CreateDynamicBody(weapon.bodyDef);

				//weapon.body.m_position.x = body.GetLocalCenter().x;
				//weapon.body.m_position.y = body.GetLocalCenter().y - 50;
				//weapon.body.m_xf.position.Set(body.GetPosition().x, body.GetPosition().y);
				
				
				//weapon.body.m_xf.position.Set((1000/parent.config.phy_scaling)-parent.scrollX, (200/parent.config.phy_scaling)-parent.scrollY);
				//weapon.body.m_rotation = 0;
				
				/*weapon.body.m_linearVelocity = parent.mouse_angle_vec;
				weapon.body.m_linearVelocity.x *= 2 * weapon.body.m_mass;
				weapon.body.m_linearVelocity.y *= 1 * weapon.body.m_mass;*/

				weapon = null;
			}
		}
		
		public function take_weapon(Wbody:b2Body)
		{
			if(weapon!=null)
				return;
			
			
			parent.level.destroy_body(false, Wbody);
			
			weapon = Wbody.m_userData;
			//parent.level.m_world.DestroyBody(Wbody);
			//parent.level.m_world.DestroyBody(weapon.body);
			//weapon.body=null;
			//Wbody=null;
			
			

			if(direction != weapon.direction)
			{
				weapon.change_carry_direction();
			}
			/*else
			{
				weapon.userData.scaleX *= -1;
				weapon.userData.scaleY *= -1;
			}*/
		}
		
		public function action()
		{
			check_correct_direction();
			
			// waffe weiter feuern
			if(weapon!=null && mouse_down==true)
			{
				if(weapon.check_for_shoot()==true)
				{
					weapon.shoot(body.GetAngle());
				}
			}
		}
		
		
		public function animation()
		{
			//trace(onGround);
			
			// images
			if(move_walk == true)
			{
				if(onGround == true || onGround == false)
				{
					if(getTimer()-frame_time_last > frame_hz)
					{
						frame_cur++;
						frame_time_last = getTimer();
					}
				}
				else
					frame_cur = 1;
				
				if(frame_cur > 8)
					frame_cur = 1;
			}
			else
				frame_cur = 1;

			userData.gotoAndStop(frame_cur);
			
			
			// rotation
			if(rotate==true)
			{
				if(getTimer() - rotate_time_last > rotate_hz)
				{
					if(rotate_direction == 0)
					{
						rotate_angle+=0.5 * ((getTimer() - rotate_time_last));
						
						//rotate_time_last = getTimer();
	
						if(rotate_angle > 350)
						{
							rotate_angle=0;
							rotate=false;
							rotate_time_last = 0;
						}
					}
					else
					{
						if(rotate_angle == 0)
							rotate_angle = 360;

						rotate_angle-=0.5 * ((getTimer() - rotate_time_last));
						
						//rotate_time_last = getTimer();
	
						if(rotate_angle < 10)
						{
							rotate_angle=0;
							rotate=false;
							rotate_time_last = 0;
						}
					}
					
					
				}
			}
			
			rotate_time_last = getTimer();
			
			body.m_sweep.a = rotate_angle *(Math.PI/180);
		}
		
		private function move(m_state:Boolean)
		{
			move_walk = m_state;
		}
		
		
		private function check_leftRight()
		{
			onLeft = false;
			onRight = false;
			
			/*for (var cn:b2ContactNode = body.m_contactList; cn != null; cn = cn.next)
			{
				var shape:b2Shape;
				shape = cn.contact.GetShape2();
	
				if(shape.m_userData == "left")
				{
					onLeft = true;
					break;
				}
				else if(shape.m_userData == "right")
				{
					onRight = true;
					break;
				}
			}*/
		}
		
		
		private function start_rotate()
		{
			if(body.m_linearVelocity.x<0)
				rotate_direction=1;
			else
				rotate_direction=0;
				
			if(body.m_linearVelocity.x==0)
				rotate_direction = direction;
				
			rotate=true;
		}
		
		public function check_correct_direction()
		{
			if(parent.f_kreuz.x > (body.GetPosition().x * parent.config.phy_scaling) - parent.scrollX)
			{
				if(direction == 1)
				{
					direction=0;
					
					if(weapon!=null)
					{
						weapon.change_carry_direction();
					}
				}
			}
			else
			{
				
				if(direction == 0)
				{
					direction=1;

					if(weapon!=null)
					{
						weapon.change_carry_direction();
					}
				}
			}
		}
		
		public function contactListener(type:String, point:b2ContactPoint)
		{
			var body_dst:b2Body = point.shape1.GetBody();
			var body_src:b2Body = point.shape2.GetBody();
			
			
			if(type=="add")
			{
				// ground
				if(point.shape2.m_userData=="ground")
				{
					//trace(getTimer() + " " + "!!! ONGROUND !!!");
					onGround = true;
					jump = 0;
				}
				
				// weapon
				if(body_dst.m_userData.type == "BWeaponGun" || body_dst.m_userData.type == "BWeaponLaserGreen")
				{
					take_weapon(body_dst);
				}
			}
			
			if(type=="remove")
			{
				// ground
				if(point.shape2.m_userData=="ground")
				{
					//trace(getTimer() + " " + "!!! NOT ONGROUND !!!");
					onGround = false;
				}
			}
			
			
		}
		
		public function mouse_control(s_name:String, i_time:int, x:int, y:int)
		{
			// action
			if(s_name == "mouse_move")
			{
				check_correct_direction();
			}
			
			else if(s_name == "mouse_down")
			{
				mouse_down = true;
				
				if(weapon!=null)
					weapon.load_time_start = getTimer()-(getTimer()-weapon.load_time_start);
			}
			
			else if(s_name == "mouse_up")
			{
				mouse_down = false;
			}
		}
		
		public function keyboard_control(s_name:String, b_state:Boolean, i_time:int)
		{
			// check onGround
			//check_onGround();
			check_leftRight();
			
			// generate velo
			var current_velo_x:Number = Math.abs(body.m_linearVelocity.x);
			var current_velo_y:Number = Math.abs(body.m_linearVelocity.y);
			
			if(current_velo_x>tmp_speed_hori / parent.config.phy_scaling)
				current_velo_x=tmp_speed_hori / parent.config.phy_scaling;
			
			// generate time-handling
			if(i_time<100)
				i_time=100;
				
			var i_time_jump_1:int = i_time;
			var i_time_jump_2:int = i_time;
			
			// generate speed
			var tmp_speed_vert:Number = (speed_vert) * (i_time/50);
			var tmp_speed_hori:Number = (speed_hori) * (i_time/50);

			if(tmp_speed_vert > speed_vert)
				tmp_speed_vert = speed_vert;
				
			if(tmp_speed_hori > speed_hori)
				tmp_speed_hori = speed_hori;
				

			// action
			if(s_name == "drop")
			{
				drop_weapon();
			}
			
			else if(s_name == "left")
			{
				if(b_state==true)
				{
					if(body.m_linearVelocity.x>0)
						body.m_linearVelocity.x = 0;
	
					var tmp_v1:b2Vec2 = body.GetWorldCenter();
					var tmp_v2:b2Vec2 = new b2Vec2(-(Math.abs(tmp_speed_hori-current_velo_x))*body.m_mass,0);
					
					if(onLeft==false)
						body.ApplyImpulse(tmp_v2, tmp_v1);
					
					move(true);
					
					if(body.m_linearVelocity.x<-speed_hori)
						body.m_linearVelocity.x = -speed_hori;
				}
				else
				{
					frame_cur = 0;
					move(false);
				}
			}
			
			else if(s_name == "right")
			{
				if(b_state==true)
				{
					if(body.m_linearVelocity.x<0)
						body.m_linearVelocity.x = 0;
					
					var tmp_v1:b2Vec2 = body.GetWorldCenter();
					var tmp_v2:b2Vec2 = new b2Vec2((Math.abs(tmp_speed_hori-current_velo_x))*body.m_mass,0);

					if(onRight==false)
						body.ApplyImpulse(tmp_v2, tmp_v1);
					
					move(true);
					
					if(body.m_linearVelocity.x>speed_hori)
						body.m_linearVelocity.x = speed_hori;
				}
				else
				{
					frame_cur = 0;
					move(false);
				}
			}
			
			else if(s_name == "up")
			{
				if(b_state==true)
				{
					if(onGround == true)
						jump = 1;

					if(jump == 1)
					{
						var tmp_v1:b2Vec2 = body.GetWorldCenter();
						var tmp_v2:b2Vec2 = new b2Vec2(0,-(Math.abs(tmp_speed_vert-current_velo_y))*body.m_mass);
						
						body.ApplyImpulse(tmp_v2, tmp_v1);
						
						if(i_time_jump_1 > 300)
						{
							jump = 0;
						}
					}
					
					if(onGround == false && jump == 2)
					{
						//trace(getTimer() + " " + direction);
						start_rotate();
					
						var tmp_v1:b2Vec2 = body.GetWorldCenter();
						var tmp_v2:b2Vec2 = new b2Vec2(0,-(Math.abs(tmp_speed_vert-current_velo_y))*body.m_mass);

						body.ApplyImpulse(tmp_v2, tmp_v1);
						
						if(i_time_jump_2 > 300)
						{
							jump = 3;
						}
					}
					
					frame_cur = 0;
					//move(true);
				}
				else
				{
					if(jump!=3)
					{
						if(jump == 2)
							jump = 3;
						else
							jump = 2;
					}
				}
			}
			
			else if(s_name == "down")
			{
				if(b_state==true)
				{
					var tmp_v1:b2Vec2 = body.GetWorldCenter();
					var tmp_v2:b2Vec2 = new b2Vec2(0,(tmp_speed_vert/5)*body.m_mass);
					body.WakeUp();
					body.ApplyImpulse(tmp_v2, tmp_v1);
				}
			}
		}
	}
}













