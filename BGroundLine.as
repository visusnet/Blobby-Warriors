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
	
	public class BGroundLine
	{
		// ### Atributes ###
		public var parent:BGame;
		
		public var userData:PhysGround;
		public var bodyDef:b2BodyDef;
		public var boxDef:b2PolygonDef;
		public var body:b2Body;
		
		public var gravity_master:Boolean = false;
		
		public var type:String = "BWall";
		
		private var rot:Number;
		
		
		public function add()
		{
			body=parent.level.m_world.CreateStaticBody(bodyDef);

			body.CreateShape(boxDef);
			
			body.m_sweep.a = rot;
		}
		
		public function BGroundLine(p:BGame, x:int, y:int, width:int, rotation:Number)
		{
			parent = p;
			var phy_scale:Number = parent.config.phy_scaling;
			
			rot = rotation/phy_scale;
			
			bodyDef = new b2BodyDef();
			
			boxDef = new b2PolygonDef();
			boxDef.SetAsBox(width/phy_scale, 10/phy_scale);
			boxDef.friction = 1;
			boxDef.categoryBits = 0x0001;

			
			bodyDef.position.Set(x/phy_scale, y/phy_scale);
			bodyDef.userData = this;
		}
	}
}













