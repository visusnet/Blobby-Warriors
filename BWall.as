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
	
	public class BWall
	{
		// ### Atributes ###
		public var userData:PhysGround;
		public var bodyDef:b2BodyDef;
		public var body:b2Body;
		
		public var gravity_master:Boolean = false;
		
		public var type:String = "BWall";
		
		public function BWall(x:int, y:int, width:int, height:int)
		{
			bodyDef = new b2BodyDef();
			var boxDef = new b2BoxDef();
			boxDef.extents.Set(width, height);
			boxDef.friction = 1;
			bodyDef.position.Set(x, y);
			bodyDef.AddShape(boxDef);
			
			
			boxDef.categoryBits = 0x0001;

			bodyDef.userData = this;
			
			userData = new PhysGround();
			userData.x = x;
			userData.y = y;
			userData.width = boxDef.extents.x * 2;
			userData.height = boxDef.extents.y * 2;
		}
		
	}
}













