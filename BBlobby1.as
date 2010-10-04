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
	
	public class BBlobby1
	{
		// ### Atributes ###
		public var parent:BGame;
		
		public var userData:BitmapData;
		
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
		
		private var onGround:Boolean=false;
		
		private var move_walk:Boolean;
		
		private var rotate_angle:int;
		private var rotate:Boolean;
		private var rotate_hz:int;
		private var rotate_time_last:uint;
		private var rotate_direction:int;
		
		private var direction:int;
		var weapon:*;
		var mouse_down:Boolean;
		
		public var groundBody_body_unten:b2Body;
		public var groundBody_left:b2Body;
		public var groundBody_middle:b2Body;
		public var groundBody_right:b2Body;
		
		
		public var gravity_master:Boolean = false;
		
		public var type:String = "BBlobby1";
		
		public var groupIndex:int;
		
		
		// Time To Life
		public var ttl_creationTime:int;
		public var ttl_timeToLive:int=-1;

		
		
		public function add()
		{
			body=parent.level.m_world.CreateBody(bodyDef);
			
			body.CreateShape(circleDef_oben);
			body.CreateShape(circleDef_unten);
			body.CreateShape(circleDef_ground1);
			body.CreateShape(circleDef_ground2);
			body.CreateShape(circleDef_ground3);
			
			body.SetMassFromShapes();
			
			/*var tmp_mass:b2MassData = new b2MassData();
			tmp_mass.mass = 20;
			tmp_mass.I = 3;
			tmp_mass.center.SetZero();
			body.SetMass(tmp_mass);*/
		}
		
		
		public function action()
		{
			if(ttl_timeToLive!=-1)
			{
				if(getTimer()-ttl_creationTime >= ttl_timeToLive)
				{
					parent.level.destroy_body(false, body);
				}
			}
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
		
		public function BBlobby1(p:BGame, x:int, y:int, image:BitmapData)
		{
			parent = p;
			var phy_scale:Number = parent.config.phy_scaling;
			
			userData = image;
			
			ttl_creationTime = getTimer();
			
			
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
			circleDef_unten.density = 1;
			circleDef_unten.friction = 1;
			circleDef_unten.restitution = 0.0;
			circleDef_unten.localPosition.Set(1 / phy_scale, 7 / phy_scale);
			circleDef_unten.userData = "body_unten"; 
			circleDef_unten.filter.categoryBits = parent.config.categoryBits_bblobby;
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
			


			//userData = new object_blobby();
			//userData.gotoAndStop(1);

			bodyDef.userData = this;
			bodyDef.position.x = x / phy_scale;
			bodyDef.position.y = y / phy_scale;
			
			bodyDef.fixedRotation = false;
			
			
			
			health_full=100;
			health = health_full;
		}
		
		
		
		public function contactListener(type:String, point:b2ContactPoint)
		{
			var body_dst:b2Body = point.shape1.GetBody();
			var body_src:b2Body = point.shape2.GetBody();
			
			
			if(type=="add")
			{
			}
			
			if(type=="remove")
			{
			}		
		}
		
	}
}