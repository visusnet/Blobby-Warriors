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
	
	public class BBlobby
	{
		// ### Atributes ###
		public var parent:BGame;
		
		public var userData:object_blobby;
		
		public var bodyDef:b2BodyDef;
		public var body:b2Body;
		
		private var speed_vert:int;
		private var speed_hori:int;
		
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
		
		// weapon stuff
		//var weapon_join:b2RevoluteJoint;
		var weapon:*;
		
		var mouse_down:Boolean;
		
		
		public var gravity_master:Boolean = false;
		
		public var type:String = "BBlobby";

		
		public function BBlobby(x:int, y:int)
		{
			speed_vert = 250;
			speed_hori = 200;
			
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
			var circleDef_oben = new b2CircleDef();
			var circleDef_unten = new b2CircleDef();
			var circleDef_ground1 = new b2CircleDef();
			var circleDef_ground2 = new b2CircleDef();
			var circleDef_ground3 = new b2CircleDef();
			var circleDef_left1 = new b2CircleDef();
			var circleDef_right1 = new b2CircleDef();
			
			circleDef_oben.radius = 13;
			circleDef_oben.density = 0.6;
			circleDef_oben.friction = 0;
			circleDef_oben.restitution = 0.6;
			circleDef_oben.localPosition.Set(0, -16);
			circleDef_oben.userData = "body_oben";
			circleDef_oben.categoryBits = 0x0004;
			bodyDef.AddShape(circleDef_oben);
			
			circleDef_unten.radius = 17;
			circleDef_unten.density = 0.6;
			circleDef_unten.friction = 1;
			circleDef_unten.restitution = 0.0;
			circleDef_unten.localPosition.Set(0, 0);
			circleDef_unten.userData = "body_unten"; 
			circleDef_unten.categoryBits = 0x0004;
			bodyDef.AddShape(circleDef_unten);
			
			circleDef_ground1.radius = 12;
			circleDef_ground1.density = 0;
			circleDef_ground1.friction = 1;
			circleDef_ground1.restitution = 0.0;
			circleDef_ground1.localPosition.Set(0, 6);
			circleDef_ground1.userData = "ground"; 
			circleDef_ground1.categoryBits = 0x0004;
			bodyDef.AddShape(circleDef_ground1);
			
			circleDef_ground2.radius = 10;
			circleDef_ground2.density = 0;
			circleDef_ground2.friction = 0;
			circleDef_ground2.restitution = 0.0;
			circleDef_ground2.localPosition.Set(-4, 6);
			circleDef_ground2.userData = "ground"; 
			circleDef_ground2.categoryBits = 0x0004;
			bodyDef.AddShape(circleDef_ground2);
			
			circleDef_ground3.radius = 10;
			circleDef_ground3.density = 0;
			circleDef_ground3.friction = 0;
			circleDef_ground3.restitution = 0.0;
			circleDef_ground3.localPosition.Set(4, 6);
			circleDef_ground3.userData = "ground"; 
			circleDef_ground3.categoryBits = 0x0004;
			bodyDef.AddShape(circleDef_ground3);
			
			circleDef_left1.radius = 5;
			circleDef_left1.density = 0;
			circleDef_left1.friction = 1;
			circleDef_left1.restitution = 0.0;
			circleDef_left1.localPosition.Set(-13, 0);
			circleDef_left1.userData = "left"; 
			circleDef_left1.categoryBits = 0x0004;
			circleDef_left1.maskBits = 0x0001;
			bodyDef.AddShape(circleDef_left1);
			
			circleDef_right1.radius = 5;
			circleDef_right1.density = 0;
			circleDef_right1.friction = 1;
			circleDef_right1.restitution = 0.0;
			circleDef_right1.localPosition.Set(13, 0);
			circleDef_right1.userData = "right"; 
			circleDef_right1.categoryBits = 0x0004;
			circleDef_right1.maskBits = 0x0001;
			bodyDef.AddShape(circleDef_right1);
			
			
			bodyDef.position.x = 450;
			bodyDef.position.y = 500;
			
			bodyDef.userData = this;
			userData = new object_blobby();
			//userData.x = 600;
			//userData.y = 50;
			//userData.width = circleDef.radius * 2; 
			//userData.height = circleDef.radius * 2;
			
			bodyDef.preventRotation = true;

			
			
			move(true);
		}
		
		public function draw_weapon()
		{
			if(weapon != null)
			{
				weapon.userData.x = body.m_position.x + weapon.blobbyX_draw - parent.scrollX;
				weapon.userData.y = body.m_position.y + weapon.blobbyY_draw -  parent.scrollY;
				weapon.userData.rotation = ( parent.mouse_angle * (180/Math.PI)) + (body.m_rotation * (180/Math.PI));
				
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
				
				weapon.body = parent.m_world.CreateBody(weapon.bodyDef);

				weapon.body.m_position.x = body.GetCenterPosition().x;
				weapon.body.m_position.y = body.GetCenterPosition().y - 50;
				//weapon.body.m_rotation = weapon.userData.rotation * 180/(Math.PI);
				weapon.body.m_rotation = 0;
				
				weapon.body.m_linearVelocity = parent.mouse_angle_vec;
				weapon.body.m_linearVelocity.x *= 2 * weapon.body.m_mass;
				weapon.body.m_linearVelocity.y *= 1 * weapon.body.m_mass;

				weapon = null;
			}
		}
		
		public function take_weapon(Wbody:b2Body)
		{
			if(weapon!=null)
				return;
				
			weapon = Wbody.m_userData;
			 parent.m_world.DestroyBody(Wbody);

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
					parent.addChild(weapon.shoot(this, parent.mouse_angle_vec, parent.m_world, parent.mouse_angle, body.m_rotation).userData);
			}
		}
		
		
		public function animation()
		{
			// images
			if(move_walk == true)
			{
				if(onGround == true)
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
			
			body.m_rotation = rotate_angle *(Math.PI/180);
		}
		
		private function move(m_state:Boolean)
		{
			move_walk = m_state;
		}
		
		
		private function check_leftRight()
		{
			onLeft = false;
			onRight = false;
			
			for (var cn:b2ContactNode = body.m_contactList; cn != null; cn = cn.next)
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
			}
		}
		
		
		private function check_onGround()
		{
			onGround = false;
			
			if(rotate == true)
				return;
			
			for (var cn:b2ContactNode = body.m_contactList; cn != null; cn = cn.next)
			{
				var shape:b2Shape;
				shape = cn.contact.GetShape2();
	
				if(shape.m_userData == "ground")
				{
					onGround = true;
					jump = 0;
					
					break;
				}
			}
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
			if(parent.f_kreuz.x>body.GetCenterPosition().x - parent.scrollX)
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
			check_onGround();
			check_leftRight();
			
			// generate velo
			var current_velo_x:int = Math.abs(body.m_linearVelocity.x);
			var current_velo_y:int = Math.abs(body.m_linearVelocity.y);
			
			if(current_velo_x>200)
				current_velo_x=200;
			
			// generate speed
			if(i_time<100)
				i_time=100;
			
			var tmp_speed_vert:int = speed_vert * (i_time/150);
			var tmp_speed_hori:int = speed_hori * (i_time/150);

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
	
					var tmp_v1:b2Vec2 = body.GetCenterPosition();
					var tmp_v2:b2Vec2 = new b2Vec2(-(Math.abs(tmp_speed_hori-current_velo_x))*body.m_mass,0);
					body.WakeUp();
					
					if(onLeft==false)
						body.ApplyImpulse(tmp_v2, tmp_v1);
					
					move(true);
					
					if(body.m_linearVelocity.x<-200)
						body.m_linearVelocity.x = -200;
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
					
					var tmp_v1:b2Vec2 = body.GetCenterPosition();
					var tmp_v2:b2Vec2 = new b2Vec2((Math.abs(tmp_speed_hori-current_velo_x))*body.m_mass,0);
					body.WakeUp();
					
					if(onRight==false)
						body.ApplyImpulse(tmp_v2, tmp_v1);
					
					move(true);
					
					if(body.m_linearVelocity.x>200)
						body.m_linearVelocity.x = 200;
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
						var tmp_v1:b2Vec2 = body.GetCenterPosition();
						var tmp_v2:b2Vec2 = new b2Vec2(0,-(Math.abs(tmp_speed_vert-current_velo_y))*body.m_mass);
						body.WakeUp();
						body.ApplyImpulse(tmp_v2, tmp_v1);
						
						if(body.m_linearVelocity.y < -speed_vert)
							jump = 0;
					}
					
					if(onGround == false && jump == 2)
					{
						start_rotate();
					
						var tmp_v1:b2Vec2 = body.GetCenterPosition();
						var tmp_v2:b2Vec2 = new b2Vec2(0,-(Math.abs(tmp_speed_vert-current_velo_y))*body.m_mass);
						body.WakeUp();
						body.ApplyImpulse(tmp_v2, tmp_v1);
						
						if(body.m_linearVelocity.y < -speed_vert)
							jump = 3;
					}
					
					frame_cur = 0;
					move(true);
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
					var tmp_v1:b2Vec2 = body.GetCenterPosition();
					var tmp_v2:b2Vec2 = new b2Vec2(0,(tmp_speed_vert/5)*body.m_mass);
					body.WakeUp();
					body.ApplyImpulse(tmp_v2, tmp_v1);
				}
			}
		}
	}
}













