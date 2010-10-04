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
		public var ki:BKI;
		public var content:String = "";
		

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
		
		
		public function add()
		{
			body=parent.level.m_world.CreateBody(bodyDef);
		
			body.CreateShape(circleDef);
			
			var tmp_mass:b2MassData = new b2MassData();
			tmp_mass.mass = 1.5;
			tmp_mass.I = 3;
			tmp_mass.center.SetZero();
			body.SetMass(tmp_mass);
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
			circleDef.restitution = 0.4;
			circleDef.filter.categoryBits = parent.config.categoryBits_bball;
			circleDef.filter.maskBits = parent.config.maskBits_bball;
			//circleDef.filter.groupIndex = -8;
			
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













