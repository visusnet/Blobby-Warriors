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
	
	public class BGroundLine
	{
		// ### Atributes ###
		public var parent:BGame;
		
		public var userData:*;
		public var bodyDef:b2BodyDef;
		public var boxDef:b2PolygonDef;
		public var body:b2Body;
		
		public var gravity_master:Boolean = false;
		
		public var type:String = "BGroundLine";
		
		private var rot:Number;
		
		public var m_angle:Number;
		public var m_angle_vec:b2Vec2;
		
		public var p1:Point;
		public var p2:Point;
		private var friction:Number;
		
		
		public function toXML():String
		{
			var xml_string:String;
			
			xml_string = "<ground_line x1='" + p1.x + "' y1='" + p1.y + "' x2='" + p2.x + "' y2='" + p2.y + "' friction='" + friction + "'></ground_line>";
			
			return xml_string;
		}
		
		public function add()
		{
			//bodyDef.angle = rot;
			
			body=parent.level.m_world.CreateBody(bodyDef);

			body.CreateShape(boxDef);
		}
		
		
		/*function makeLine(p1:Point, p2:Point) : b2PolygonDef
		{
			 //the body is just a new body you created
			 var polygonDef = new b2PolygonDef();
			 var xOffset:Number = p2.x - p1.x;
			 var yOffset:Number = p2.y - p1.y;
			 var length = Math.sqrt((xOffset * xOffset) + (yOffset * yOffset));
			 var angle = Math.atan2(yOffset, xOffset);
			 polygonDef.SetAsBox(length, 1);
			 
			 
			 angle = angle * (180/Math.PI);
			 
			 trace(m_angle + " : " + angle);
			 
			 
			 bodyDef.angle = angle;
			 bodyDef.position = new b2Vec2(p1.x - Math.cos(angle) * length , p1.y - Math.sin(angle) * length);
			 
			 
			 return polygonDef;
			 
			 //body.CreateShape(polygonDef);
			 //body.SetXForm(b2Vec2(p1.x - cos(angle) * length , p1.y - sin(angle) * length), angle);
		}*/
		
		function makeLine(p1:Point, p2:Point) : b2PolygonDef
		{
			 var polygonDef = new b2PolygonDef();
			 
			 var xOffset:Number = p2.x - p1.x;
			 var yOffset:Number = p2.y - p1.y;
			 xOffset = xOffset > 0 ? xOffset : -xOffset;
			 yOffset = yOffset > 0 ? yOffset : -yOffset;
			 if(yOffset > xOffset)
			 {
				  xOffset = parent.config.groundline_height / parent.config.phy_scaling;
				  yOffset = 0;
			  }
			 else
			 {
				  xOffset = 0;
				  yOffset = parent.config.groundline_height / parent.config.phy_scaling;
			 }
		
			 polygonDef.vertices[0].x = p1.x;
			 polygonDef.vertices[0].y = p1.y;
			 polygonDef.vertices[1].x = p2.x;
			 polygonDef.vertices[1].y = p2.y;
			 polygonDef.vertices[2].x = p2.x + xOffset;
			 polygonDef.vertices[2].y = p2.y + yOffset;
			 polygonDef.vertices[3].x = p1.x + xOffset;
			 polygonDef.vertices[3].y = p1.y + yOffset;
			 polygonDef.vertexCount = 4;
			 
			 return polygonDef;
		}
		
		public function calc_angle(p1:Point, p2:Point)
		{
			var a:int = p2.y - p1.y;
			var b:int = p2.x - p1.x;

			m_angle = Math.atan2(a, b);
			m_angle_vec = parent.rad2vec(m_angle);
		}
		
		
		public function BGroundLine(p:BGame, p1:Point, p2:Point, friction:Number)
		{
			parent = p;
			var phy_scale:Number = parent.config.phy_scaling;
			
			this.p1 = p1;
			this.p2 = p2;
			this.friction = friction;
			
			bodyDef = new b2BodyDef();
			bodyDef.userData = this;
			bodyDef.isBullet = true;
			
			calc_angle(p1,p2);
			
			boxDef = makeLine(new Point(p1.x/phy_scale,p1.y/phy_scale),new Point(p2.x/phy_scale,p2.y/phy_scale));
			boxDef.friction = friction;
			boxDef.filter.categoryBits = parent.config.categoryBits_bgroundline;
			boxDef.filter.maskBits = parent.config.maskBits_bgroundline;

			
		}
	}
}













