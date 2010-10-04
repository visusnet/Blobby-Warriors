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
	
	public class BCrate
	{
		// ### Atributes ###
		public var userData:object_crate;
		public var bodyDef:b2BodyDef;
		public var body:b2Body;
		
		public var gravity_master:Boolean = false;
		
		public var type:String = "BCrate";
		
		public function BCrate(x:int, y:int)
		{
			bodyDef = new b2BodyDef();
			var boxDef = new b2BoxDef();
			boxDef.extents.Set(12.5, 12.5);
			boxDef.density = 0.2;
			boxDef.friction = 0.7;
			boxDef.restitution = 0.1;
			bodyDef.position.Set(x, y);
			bodyDef.AddShape(boxDef);
			
			
			boxDef.categoryBits = 0x0002;

			bodyDef.userData = this;
			
			userData = new object_crate();
			userData.x = x;
			userData.y = y;
			userData.width = boxDef.extents.x * 2;
			userData.height = boxDef.extents.y * 2;
			userData.smooth = true;
		}
		
	}
}













