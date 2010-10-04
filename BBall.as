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
	
	public class BBall
	{
		// ### Atributes ###
		public var parent:BGame;
		
		public var userData:object_ball;
		public var bodyDef:b2BodyDef;
		public var body:b2Body;
		public var circleDef;
		
		public var gravity_master:Boolean = false;
		
		public var type:String = "BBall";

		public function add()
		{
			body=parent.level.m_world.CreateDynamicBody(bodyDef);
			parent.addChild(userData);
			
			body.CreateShape(circleDef);
			
			//body.SetMassFromShapes();
			
			var tmp_mass:b2MassData = new b2MassData();
			tmp_mass.mass = 1.5;
			tmp_mass.I = 3;
			tmp_mass.center.SetZero();
			body.SetMass(tmp_mass);
			
			/*var tmp_mass:b2MassData = new b2MassData();
			tmp_mass.mass = 1.5;
			tmp_mass.center = body.GetLocalCenter();
			body.SetMass(tmp_mass);*/
		}
		
		public function bdraw()
		{
			var trans_x:Number = 15;
			var trans_y:Number = 15;
			var trans_x2:Number = 0;
			var trans_y2:Number = 0;
			
			var angle_in_radians = body.GetAngle();
			
			var rotationMatrix:Matrix = new Matrix();
			rotationMatrix.translate(-trans_x,-trans_y);
			rotationMatrix.rotate(angle_in_radians);
			rotationMatrix.translate(trans_x,trans_y);
			
			rotationMatrix.tx += trans_x2;
			rotationMatrix.ty += trans_y2;
			
			var matrixImage:BitmapData = new BitmapData(30, 30, true, 0x00000000);
			matrixImage.draw(userData, rotationMatrix);
		
			var playerRect:Rectangle = new Rectangle(0,0,30,30);
			var playerPoint:Point=new Point(((body.GetPosition().x-(trans_x+trans_x2)/parent.config.phy_scaling) * parent.config.phy_scaling) - parent.scrollX,((body.GetPosition().y-(trans_y+trans_y2)/parent.config.phy_scaling) * parent.config.phy_scaling) - parent.scrollY);
			parent.canvasBD.copyPixels(matrixImage, playerRect, playerPoint);
		}
		
		public function BBall(p:BGame, x:int, y:int)
		{
			parent = p;
			var phy_scale:Number = parent.config.phy_scaling;
			
			bodyDef = new b2BodyDef();
			circleDef = new b2CircleDef();
			
			circleDef.radius = 15 / phy_scale;
			circleDef.density = 1;
			circleDef.friction = 0.5;
			circleDef.restitution = 0.3;
			circleDef.categoryBits = 0x0002;
			
			bodyDef.position.x = x / phy_scale;
			bodyDef.position.y = y / phy_scale;
			bodyDef.userData = this;
			//bodyDef.massData.mass = 2;
			
			userData = new object_ball();
			userData.x = x;
			userData.y = y;
			userData.width = (circleDef.radius * 2) * phy_scale; 
			userData.height = (circleDef.radius * 2) * phy_scale; 

			//bodyDef.isBullet = true;
		}
		
	}
}













