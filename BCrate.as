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
	
	public class BCrate
	{
		// ### Atributes ###
		public var parent:BGame;
		
		public var userData:object_crate;
		public var bodyDef:b2BodyDef;
		public var boxDef:b2PolygonDef;
		public var body:b2Body;
		
		public var gravity_master:Boolean = false;
		
		public var type:String = "BCrate";
		
		
		public function add()
		{
			body=parent.level.m_world.CreateDynamicBody(bodyDef);
			parent.addChild(userData);
			
			body.CreateShape(boxDef);
			
			//body.SetMassFromShapes();
			
			var tmp_mass:b2MassData = new b2MassData();
			tmp_mass.mass = 3.5;
			tmp_mass.I = 3;
			tmp_mass.center.SetZero();
			body.SetMass(tmp_mass);
		}
		
		public function bdraw()
		{
			var trans_x:Number = 13;
			var trans_y:Number = 13;
			var trans_x2:Number = 4;
			var trans_y2:Number = 4;
			
			var angle_in_radians = body.GetAngle();
			
			var rotationMatrix:Matrix = new Matrix();
			rotationMatrix.translate(-trans_x,-trans_y);
			rotationMatrix.rotate(angle_in_radians);
			rotationMatrix.translate(trans_x,trans_y);
			
			rotationMatrix.tx += trans_x2;
			rotationMatrix.ty += trans_y2;
			
			var matrixImage:BitmapData = new BitmapData(34, 34, true, 0x00000000);
			matrixImage.draw(userData, rotationMatrix);
		
			var playerRect:Rectangle = new Rectangle(0,0,34,34);
			var playerPoint:Point=new Point(((body.GetPosition().x-(trans_x+trans_x2)/parent.config.phy_scaling) * parent.config.phy_scaling) - parent.scrollX,((body.GetPosition().y-(trans_y+trans_y2)/parent.config.phy_scaling) * parent.config.phy_scaling) - parent.scrollY);
			parent.canvasBD.copyPixels(matrixImage, playerRect, playerPoint);
		}
		
		public function BCrate(p:BGame, x:int, y:int)
		{
			parent = p;
			var phy_scale:Number = parent.config.phy_scaling;
			
			bodyDef = new b2BodyDef();
			
			boxDef = new b2PolygonDef();
			boxDef.SetAsBox(12.5/phy_scale, 12.5/phy_scale);
			boxDef.density = 1;
			boxDef.friction = 0.7;
			boxDef.restitution = 0.1;
			boxDef.categoryBits = 0x0002;
			
			bodyDef.position.Set(x/phy_scale, y/phy_scale);
			bodyDef.userData = this;
			//bodyDef.massData.mass = 200;
			
			userData = new object_crate();
			userData.x = x;
			userData.y = y;
			userData.width = 12.5 * 2;
			userData.height = 12.5 * 2;
			userData.smooth = true;
			userData.rotation = 20;
		}
		
	}
}













