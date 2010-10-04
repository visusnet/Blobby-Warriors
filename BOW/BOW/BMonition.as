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
	
	public class BMonition
	{
		// ### Atributes ###
		public var parent:BGame;
		
		public var userData:*;
		public var bodyDef:b2BodyDef;
		public var body:b2Body;
		public var gravity_master:Boolean = true;
		public var type:String;
		public var mass:Number;
		public var shapeDef:*;
		public var damage:Number;
		
		// Time To Life
		public var ttl_creationTime:int;
		public var ttl_timeToLive:int=-1;
		
		
		public function add()
		{
			bodyDef.isBullet = true;
			
			body=parent.level.m_world.CreateBody(bodyDef);
			
			body.CreateShape(shapeDef);
			
			var tmp_mass:b2MassData = new b2MassData();
			tmp_mass.mass = mass;
			tmp_mass.I = 3;
			tmp_mass.center.SetZero();
			body.SetMass(tmp_mass);
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
			var trans_x:Number = 8/2;
			var trans_y:Number = 8/2;
			var trans_x2:Number = 0;
			var trans_y2:Number = 0;
			
			var angle_in_radians = body.GetAngle();
			
			var rotationMatrix:Matrix = new Matrix();
			rotationMatrix.translate(-trans_x,-trans_y);
			rotationMatrix.rotate(angle_in_radians);
			rotationMatrix.translate(trans_x,trans_y);
			
			rotationMatrix.tx += trans_x2;
			rotationMatrix.ty += trans_y2;
			
			var matrixImage:BitmapData = new BitmapData(8, 8, true, 0x00000000);
			matrixImage.draw(userData, rotationMatrix);
		
			var playerRect:Rectangle = new Rectangle(0,0,8,8);
			var playerPoint:Point=new Point(((body.GetPosition().x-(trans_x+trans_x2)/parent.config.phy_scaling) * parent.config.phy_scaling) - parent.scrollX,((body.GetPosition().y-(trans_y+trans_y2)/parent.config.phy_scaling) * parent.config.phy_scaling) - parent.scrollY);
			parent.canvasBD.copyPixels(matrixImage, playerRect, playerPoint);
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
				parent.level.destroy_body(false, body_src);

				if(body_dst.GetUserData().type == "BCrateDDD" || body_dst.GetUserData().type == "BBlobby")
				{
					// health abziehen
					body_dst.GetUserData().health -= damage;
					if(body_dst.GetUserData().health<0)
						body_dst.GetUserData().health = 0;
						
					trace(getTimer() + " " + body_dst.GetUserData().health + " " + body_dst.GetUserData().type);
				}
			}
		}
	}
}













