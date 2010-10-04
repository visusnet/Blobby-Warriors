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
	
	public class BMonitionLaserGreen
	{
		// ### Atributes ###
		public var userData:object_monitionLaserGreen;
		public var bodyDef:b2BodyDef;
		public var body:b2Body;
		
		public var gravity_master:Boolean = true;
		
		public var type:String = "BMonitionLaserGreen";
		
		public function BMonitionLaserGreen(x:int, y:int)
		{
			bodyDef = new b2BodyDef();
			
			/*var circleDef = new b2CircleDef();
			circleDef.radius = 3;
			circleDef.density = 0.7;
			circleDef.friction = 0.5;
			circleDef.restitution = 0.7;
			circleDef.maskBits = 0x0002;*/
			
			var boxDef = new b2BoxDef();
			boxDef.extents.Set(10, 5);
			boxDef.friction = 1;
			boxDef.density = 0.65;
			boxDef.friction = 0.5;
			boxDef.maskBits = 0x0002 | 0x0001;
			
			bodyDef.AddShape(boxDef);
			
			
			bodyDef.position.x = x;
			bodyDef.position.y = y;
			bodyDef.userData = this;
			
			userData = new object_monitionLaserGreen();
			//userData.x = 500;
			//userData.y = 50;
			userData.width = boxDef.extents.x; 
			userData.height = boxDef.extents.y;
			
			//bodyDef.isBullet = true;


			//bodyDef.linearDamping = 0.05;
    		//bodyDef.angularDamping = 0.1;
			//bodyDef.rotation = 10;
		}
		
	}
}













