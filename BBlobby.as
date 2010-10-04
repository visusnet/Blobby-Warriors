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
		public var id:String;
		
		public var userData:object_blobby;
		
		public var health:Number;
		public var health_full:Number
		
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
		
		public var frame_cur:int;
		private var frame_max:int;
		private var frame_hz:int;
		private var frame_time_last:uint;
		
		public var onGround:Boolean=false;
		
		private var move_walk:Boolean;
		
		public var rotate_angle:int;
		private var rotate:Boolean;
		private var rotate_hz:int;
		private var rotate_time_last:uint;
		private var rotate_direction:int;
		
		private var direction:int;
		var weapon:*;
		var weapon_array:Array;
		var mouse_down:Boolean;
		
		public var groundBody_body_unten:b2Body;
		public var groundBody_left:b2Body;
		public var groundBody_middle:b2Body;
		public var groundBody_right:b2Body;
		
		
		public var gravity_master:Boolean = false;
		
		public var type:String = "BBlobby";
		public var ki:BKI;
		public var content:String = "255,255,255";
		
		public var groupIndex:int;
		
		public var images:Array;
		public var color_r:int=200;
		public var color_g:int=0;
		public var color_b:int=0;

		
		
		public function toXML():String
		{
			var xml_string:String;
			
			var tmp_position:Point = new Point(body.GetPosition().x * parent.config.phy_scaling, body.GetPosition().y * parent.config.phy_scaling);
			
			// ki id
			var ki_id:int = -1;
			if(ki != null)
				ki_id = ki.id;
				
			xml_string = "<object type='" + type + "' posx='" + tmp_position.x + "' posy='" + tmp_position.y + "' rotation='" + body.GetAngle() + "' ki='" + ki_id + "' content='" + content + "'></object>";
			
			return xml_string;
		}
		
		
		public function GetDirection(): int
		{
			return direction;
		}
		
		
		private function color_bitmapdata(bmp:BitmapData, new_r:int, new_g:int, new_b:int)
		{
			// bitmap manu
			bmp.lock();
			
			for (var xx:int = 0; xx < userData.width; xx++)
			{
				for (var yy:int = 0; yy < userData.height; yy++)
				{
					// Get Pixel
					var pixel:uint = bmp.getPixel(xx,yy);

					// Get RGB
					var rr:int = pixel >> 16;
					var tmp:int = pixel ^ rr << 16;
					var rg:int = tmp >> 8;
					var rb:int = tmp ^ rg << 8;
					
					// Coloring
					rr = (rr * new_r) >> 8;
					rg = (rg * new_g) >> 8;
					rb = (rb * new_b) >> 8;
					
					var fak:int = rr * 5 - 4 * 256 - 138;
					
					
					var colorkey:Boolean = !(rr | rg | rb);

					/*if (fak > 0)
					{
						rr += fak;
						rg += fak;
						rb += fak;
					}*/
					rr = rr < 255 ? rr : 255;
					rg = rg < 255 ? rg : 255;
					rb = rb < 255 ? rb : 255;
					
					
					// This is clamped to 1 because dark colors would be
					// colorkeyed otherwise
					if (colorkey)
					{
						rr = 0;
						rg = 0;
						rb = 0;
					}
					else
					{
						// rr = bedingung ? wert-fuer-true : wert-fuer-false;
						rr = rr > 0 ? rr : 1;
						rg = rg > 0 ? rg : 1;
						rb = rb > 0 ? rb : 1;
					}
 
 
 					var new_color:int = rr << 16 ^ rg << 8 ^ rb;
 					bmp.setPixel(xx, yy, new_color);
				}
			}
			
			bmp.unlock();
			
			return bmp;
		}
		
		private function create_images_from_userdata()
		{
			images = new Array();
			
			for(var i:int = 0; i<8; i++)
			{
				userData.gotoAndStop(i+1);
				
				var tmp_bmp:BitmapData = new BitmapData(userData.width, userData.height, true, 0x00000000);
				tmp_bmp.draw(userData);
				
				tmp_bmp = color_bitmapdata(tmp_bmp, color_r, color_g, color_b);
				
				//tmp_bmp.colorTransform(new Rectangle(0,0,userData.width,userData.height), new ColorTransform(0.5, 0.5, 0.5, 1, 255, 0, 0, 0));				
				
				images.push(tmp_bmp);
			}
		}
		
		
		
		
		
		public function destroy()
		{
			var test_blobby1:BBlobby1 = new BBlobby1(parent,body.GetPosition().x * parent.config.phy_scaling,body.GetPosition().y * parent.config.phy_scaling, images[0]);
			test_blobby1.add();
			
			test_blobby1.body.m_linearVelocity = new b2Vec2(body.m_linearVelocity.x, body.m_linearVelocity.y);
			
			drop_weapon();
			
			
			// level-info
			for each(var pl:BPlayer in parent.level.player_array)
			{
				if(pl.object == this)
				{
					pl.dead_time = getTimer();
				}
			}
			
			//ki = null;
		}
		
		
		public function add()
		{
			body=parent.level.m_world.CreateBody(bodyDef);
			
			body.CreateShape(circleDef_oben);
			body.CreateShape(circleDef_unten);
			body.CreateShape(circleDef_ground1);
			body.CreateShape(circleDef_ground2);
			body.CreateShape(circleDef_ground3);
			/*body.CreateShape(circleDef_left1);
			body.CreateShape(circleDef_right1);*/
			
			//body.SetMassFromShapes();
			
			var tmp_mass:b2MassData = new b2MassData();
			tmp_mass.mass = 20;
			tmp_mass.I = 3;
			tmp_mass.center.SetZero();
			body.SetMass(tmp_mass);
			
			
			/*var phy_scale:Number = parent.config.phy_scaling;
			
			var s:b2Shape;
			
			for(s = body.GetShapeList(); s; s = s.GetNext())
			{
				if(s.m_userData == "body_oben")
					s.localPosition.Set(1 / phy_scale, -9 / phy_scale);
			}*/
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
			//matrixImage.draw(userData, rotationMatrix);
			matrixImage.draw(new Bitmap(images[frame_cur-1]), rotationMatrix);


			var playerRect:Rectangle = new Rectangle(0,0,60,60);
			var playerPoint:Point=new Point(((body.GetPosition().x-(trans_x+trans_x2)/parent.config.phy_scaling) * parent.config.phy_scaling) - parent.scrollX,((body.GetPosition().y-(trans_y+trans_y2)/parent.config.phy_scaling) * parent.config.phy_scaling) - parent.scrollY);
			parent.canvasBD.copyPixels(matrixImage, playerRect, playerPoint);
		}
		
		public function create(x:int, y:int)
		{
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
			
			groupIndex = -getTimer();
			
			
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
			circleDef_oben.restitution = 0.0;
			circleDef_oben.localPosition.Set(1 / phy_scale, -9 / phy_scale);
			circleDef_oben.userData = "body_oben";
			circleDef_oben.filter.categoryBits = parent.config.categoryBits_bblobby;
			circleDef_oben.filter.maskBits = parent.config.maskBits_bblobby;
			circleDef_oben.filter.groupIndex = groupIndex;
	
			circleDef_unten.radius = 17 / phy_scale;
			circleDef_unten.density = 0.6;
			circleDef_unten.friction = 1;
			circleDef_unten.restitution = 0.0;
			circleDef_unten.localPosition.Set(1 / phy_scale, 7 / phy_scale);
			circleDef_unten.userData = "body_unten"; 
			circleDef_unten.filter.categoryBits = 0x0000;
			circleDef_unten.filter.maskBits = parent.config.maskBits_bblobby;
			circleDef_unten.filter.groupIndex = groupIndex;
			
			circleDef_ground1.radius = 12 / phy_scale;
			circleDef_ground1.density = 0;
			circleDef_ground1.friction = 1;
			circleDef_ground1.restitution = 0.0;
			circleDef_ground1.localPosition.Set(1 / phy_scale, 12 / phy_scale);
			circleDef_ground1.userData = "ground_middle"; 
			circleDef_ground1.filter.categoryBits = parent.config.categoryBits_bblobby;
			circleDef_ground1.filter.maskBits = parent.config.maskBits_bblobby;
			circleDef_ground1.filter.groupIndex = groupIndex;

			circleDef_ground2.radius = 10 / phy_scale;
			circleDef_ground2.density = 0;
			circleDef_ground2.friction = 1;
			circleDef_ground2.restitution = 0.0;
			circleDef_ground2.localPosition.Set(-5 / phy_scale, 10 / phy_scale);
			circleDef_ground2.userData = "ground_left"; 
			circleDef_ground2.filter.categoryBits = parent.config.categoryBits_bblobby;
			circleDef_ground2.filter.maskBits = parent.config.maskBits_bblobby;
			circleDef_ground2.filter.groupIndex = groupIndex;
			
			circleDef_ground3.radius = 10 / phy_scale;
			circleDef_ground3.density = 0;
			circleDef_ground3.friction = 1;
			circleDef_ground3.restitution = 0.0;
			circleDef_ground3.localPosition.Set(7 / phy_scale, 10 / phy_scale);
			circleDef_ground3.userData = "ground_right";
			circleDef_ground3.filter.categoryBits = parent.config.categoryBits_bblobby;
			circleDef_ground3.filter.maskBits = parent.config.maskBits_bblobby;
			circleDef_ground3.filter.groupIndex = groupIndex;
			
			/*circleDef_left1.radius = 5 / phy_scale;
			circleDef_left1.density = 0;
			circleDef_left1.friction = 1;
			circleDef_left1.restitution = 0.0;
			circleDef_left1.localPosition.Set(-13 / phy_scale, 0 / phy_scale);
			circleDef_left1.userData = "left"; 
			circleDef_left1.filter.categoryBits = 0x0004;
			//circleDef_left1.filter.maskBits = 0x0001;
			//bodyDef.AddShape(circleDef_left1);
			
			circleDef_right1.radius = 5 / phy_scale;
			circleDef_right1.density = 0;
			circleDef_right1.friction = 1;
			circleDef_right1.restitution = 0.0;
			circleDef_right1.localPosition.Set(13 / phy_scale, 0 / phy_scale);
			circleDef_right1.userData = "right"; 
			circleDef_right1.filter.categoryBits = 0x0004;
			//circleDef_right1.filter.maskBits = 0x0001;
			//bodyDef.AddShape(circleDef_right1);*/
			
			

			


			userData = new object_blobby();

			bodyDef.userData = this;
			bodyDef.position.x = x / phy_scale;
			bodyDef.position.y = y / phy_scale;
			
			bodyDef.fixedRotation=true;
			
			
			// create images
			create_images_from_userdata();
			
			
			health_full=100;
			health = health_full;
			
			weapon_array = new Array();
		}
		
		public function BBlobby(p:BGame, x:int, y:int)
		{
			parent = p;
			id = getTimer()*Math.random() + "-" + getTimer() + "-" + Math.random();
			
			create(x,y);
		}
		
		public function draw_weapon()
		{
			if(weapon != null)
			{
				weapon.bdraw_carry(body);
			}
		}
		
		public function drop_weapon()
		{
			if(weapon!=null)
			{
				weapon.create(0,0,false);
				
				weapon.carrier = null;
				weapon.add();
				
				weapon.body.SetXForm(new b2Vec2(body.GetPosition().x + (0/parent.config.phy_scaling), body.GetPosition().y - (40/parent.config.phy_scaling)), 0);

 				var tmp_speed:int=100;
				if(direction==1)
					tmp_speed*=-1;
					
				weapon.body.ApplyImpulse(new b2Vec2(tmp_speed/parent.config.phy_scaling,-70/parent.config.phy_scaling),weapon.body.GetWorldCenter());
				
				weapon_array[weapon.pos] = null;
				weapon = null;
			}
		}
		
		public function take_weapon(Wbody:b2Body)
		{
			if(weapon_array[Wbody.GetUserData().pos] != null)
				return;

				
			parent.level.destroy_body(false, Wbody);
			
			
			weapon_array[Wbody.GetUserData().pos] = Wbody.GetUserData();
			weapon_array[Wbody.GetUserData().pos].carrier = this.body;
			
			
			change_weapon(weapon_array[Wbody.GetUserData().pos]);
		}
		
		public function change_weapon(wp:*)
		{
			weapon = wp;
			weapon.carrier = this.body;
			
			
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
			// ki
			if(ki!=null)
				ki.step();
				
				
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
			
			body.m_sweep.a = rotate_angle *(Math.PI/180);
		}
		
		private function move(m_state:Boolean)
		{
			move_walk = m_state;
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
			if(weapon==null)
				return;
				
			if(weapon.angle_middle <= 1.7 && weapon.angle_middle >= -1.6)
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

		public function contactListener(type:String, point:b2ContactPoint, firstPos:Boolean)
		{
			var shape_src:b2Shape;
			var shape_dst:b2Shape;
			
			if(firstPos == false)
			{
				shape_src = point.shape2;
				shape_dst = point.shape1;
			}
			else
			{
				shape_src = point.shape1;
				shape_dst = point.shape2;
			}
			
			var body_src:b2Body = shape_src.GetBody();
			var body_dst:b2Body = shape_dst.GetBody();
			
			

			
			if(type=="add")
			{
				// ground
				if( body_dst.GetUserData().type != "BMonitionGun" &&
					body_dst.GetUserData().type != "BMonitionLaserGreen")
				{
					if(shape_src.GetUserData()=="body_unten" || shape_src.GetUserData()=="ground_left" || shape_src.GetUserData()=="ground_middle" || shape_src.GetUserData()=="ground_right")
					{
						if(shape_src.GetUserData()=="body_unten")
							groundBody_body_unten = body_dst;
							
						if(shape_src.GetUserData()=="ground_left")
							groundBody_left = body_dst;
							
						if(shape_src.GetUserData()=="ground_middle")
							groundBody_middle = body_dst;
	
						if(shape_src.GetUserData()=="ground_right")
							groundBody_right = body_dst;
						
						onGround = true;
					}
				}
				
				// weapon
				if(body_dst.GetUserData().type == "BWeaponGun" || body_dst.GetUserData().type == "BWeaponLaserGreen")
				{
					take_weapon(body_dst);
				}
			}
			
			if(type=="remove")
			{
				// ground
				if(shape_src.GetUserData()=="body_unten" || shape_src.GetUserData()=="ground_left" || shape_src.GetUserData()=="ground_middle" || shape_src.GetUserData()=="ground_right")
				{
					onGround = false;
				}
				
				if(shape_src.GetUserData()=="body_unten")
					groundBody_body_unten = null;
					
				if(shape_src.GetUserData()=="ground_left")
					groundBody_left = null;
					
				if(shape_src.GetUserData()=="ground_middle")
					groundBody_middle = null;
					
				if(shape_src.GetUserData()=="ground_right")
					groundBody_right = null;
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
		
		
		public function move_left(speed:Number)
		{
			if(body.m_linearVelocity.x>0)
				body.m_linearVelocity.x = 0;

			
			var tmp_ground_body:b2Body;
			
			if(groundBody_left!=null)
				tmp_ground_body = groundBody_left;
			else
				tmp_ground_body = groundBody_middle;
			
			var tmp_v1:b2Vec2 = body.GetWorldCenter();
			var tmp_v2:b2Vec2;
				
			if(speed>speed_hori)
					speed=speed_hori;
					
			if(tmp_ground_body!=null)
			{
				// Speed an Steigung berechnen / runterschrauben
				var percent_steigung:Number;
				var ground_body_angle:Number;
				
				if(tmp_ground_body.GetUserData().type=="BGroundLine")
				{
					percent_steigung = ( (tmp_ground_body.GetUserData().m_angle * (180/Math.PI)) / 90) * 100;
					ground_body_angle = tmp_ground_body.GetUserData().m_angle;
				}
				else
				{
					percent_steigung = 0;
					ground_body_angle = 0;
				}
				
				// Vector anhand GroundBody berechnen
				speed = (speed/100)*(100-percent_steigung);
				
				var len:int = -(Math.abs(speed))*body.m_mass;
				var new_a:int = Math.sin(ground_body_angle)*len;
				var new_b:int = Math.cos(ground_body_angle)*len;

				tmp_v2 = new b2Vec2(new_b, new_a);
			}
			else
				tmp_v2 = new b2Vec2(-(Math.abs(speed))*body.m_mass, 0);

			body.ApplyImpulse(tmp_v2, tmp_v1);
			
			move(true);
			
			// Max Speed-Controlling
			max_speed_control();
		}
		
		
		public function move_right(speed:Number)
		{
			if(body.m_linearVelocity.x<0)
				body.m_linearVelocity.x = 0;
			
			
			var tmp_ground_body:b2Body;
			
			if(groundBody_right!=null)
				tmp_ground_body = groundBody_right;
			else
				tmp_ground_body = groundBody_middle;

			var tmp_v1:b2Vec2 = body.GetWorldCenter();
			var tmp_v2:b2Vec2;
			
			if(speed>speed_hori)
					speed=speed_hori;
				
			if(tmp_ground_body!=null)
			{
				// Speed an Steigung berechnen / runterschrauben
				var percent_steigung:Number;
				var ground_body_angle:Number;
				
				if(tmp_ground_body.GetUserData().type=="BGroundLine")
				{
					percent_steigung = ( (Math.abs(tmp_ground_body.GetUserData().m_angle) * (180/Math.PI)) / 90) * 100;
					ground_body_angle = tmp_ground_body.GetUserData().m_angle;
				}
				else
				{
					percent_steigung = 0;
					ground_body_angle = 0;
				}
					
					
				// Vector anhand GroundBody berechnen
				speed = (speed/100)*(100-percent_steigung);

				var len:int = (Math.abs(speed))*body.m_mass;
				var new_a:int = Math.sin(ground_body_angle)*len;
				var new_b:int = Math.cos(ground_body_angle)*len;
				
				tmp_v2 = new b2Vec2(new_b, new_a);
			}
			else
				tmp_v2 = new b2Vec2((Math.abs(speed))*body.m_mass, 0);

			body.ApplyImpulse(tmp_v2, tmp_v1);
			
			move(true);
			
			// Max Speed-Controlling
			max_speed_control();
		}
		
		
		private function max_speed_control()
		{
			if(body.m_linearVelocity.x > 0 && body.m_linearVelocity.x > speed_hori)
				body.m_linearVelocity.x = speed_hori;
			else if(body.m_linearVelocity.x < 0 && body.m_linearVelocity.x < -speed_hori)
				body.m_linearVelocity.x = -speed_hori;
				
			if(body.m_linearVelocity.y < 0 && body.m_linearVelocity.y < -speed_hori)
				body.m_linearVelocity.y = -speed_hori;
		}
		
		public function is_onGround() : Boolean
		{
			if(onGround==true)
			{
				var tmp_found:Boolean = false;
				
				if(groundBody_left!=null)
					if(groundBody_left.GetUserData().type=="BGroundLine")
					{
						if(Math.abs(groundBody_left.GetUserData().m_angle) * (180/Math.PI) < parent.config.border_angle_jump)
							tmp_found = true;
					}
					else
						tmp_found = true;
						
				if(groundBody_middle!=null)
					if(groundBody_middle.GetUserData().type=="BGroundLine")
					{
						if(Math.abs(groundBody_middle.GetUserData().m_angle) * (180/Math.PI) < parent.config.border_angle_jump)
							tmp_found = true;
					}
					else
						tmp_found = true;
						
				if(groundBody_right!=null)
					if(groundBody_right.GetUserData().type=="BGroundLine")
					{
						if(Math.abs(groundBody_right.GetUserData().m_angle) * (180/Math.PI) < parent.config.border_angle_jump)
							tmp_found = true;
					}
					else
						tmp_found = true;
				
				if(tmp_found == true || (groundBody_left==null && groundBody_middle==null && groundBody_right==null))
					return true;
				else
					return false;
			}
			else
				return false;			
		}
		
		
		public function keyboard_control(s_name:String, b_state:Boolean, i_time:int)
		{
			// generate velo
			var current_velo_x:Number = Math.abs(body.m_linearVelocity.x);
			var current_velo_y:Number = Math.abs(body.m_linearVelocity.y);
			
			//if(current_velo_x>tmp_speed_hori / parent.config.phy_scaling)
			//	current_velo_x=tmp_speed_hori / parent.config.phy_scaling;
			
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
			
			
			// Vecs
			var tmp_v1:b2Vec2;
			var tmp_v2:b2Vec2;

			// action
			if(s_name == "drop")
			{
				drop_weapon();
			}
			
			else if(s_name == "left")
			{
				if(b_state==true)
				{
					move_left(tmp_speed_hori-current_velo_x);
				}
				else
				{
					frame_cur = 1;
					move(false);
				}
			}
			
			else if(s_name == "right")
			{
				if(b_state==true)
				{
					move_right(tmp_speed_hori-current_velo_x);
				}
				else
				{
					frame_cur = 1;
					move(false);
				}
			}
			
			else if(s_name == "up")
			{
				if(b_state==true)
				{
					if(is_onGround() == true)
						jump = 1;

					if(jump == 1)
					{
						tmp_v1 = body.GetWorldCenter();
						tmp_v2 = new b2Vec2(0,-(Math.abs(tmp_speed_vert-current_velo_y))*body.m_mass);
						
						body.ApplyImpulse(tmp_v2, tmp_v1);
						
						if(i_time_jump_1 > 300)
						{
							jump = 0;
						}
					}
					
					else if(is_onGround() == false && jump == 2)
					{
						//trace(getTimer() + " " + jump);
						start_rotate();
					
						tmp_v1 = body.GetWorldCenter();
						tmp_v2 = new b2Vec2(0,-(Math.abs(tmp_speed_vert-current_velo_y))*body.m_mass);

						body.ApplyImpulse(tmp_v2, tmp_v1);
						
						if(i_time_jump_2 > 300)
						{
							jump = 3;
						}
					}
					
					frame_cur = 1;
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
					tmp_v1 = body.GetWorldCenter();
					tmp_v2 = new b2Vec2(0,(tmp_speed_vert/5)*body.m_mass);
					body.WakeUp();
					body.ApplyImpulse(tmp_v2, tmp_v1);
				}
			}
		}
	}
}













