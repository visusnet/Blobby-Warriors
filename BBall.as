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
	
	public class BBall
	{
		// ### Atributes ###
		public var userData:object_ball;
		public var bodyDef:b2BodyDef;
		public var body:b2Body;
		
		public var gravity_master:Boolean = false;
		
		public var type:String = "BBall";
		
		public function BBall(x:int, y:int)
		{
			bodyDef = new b2BodyDef();
			var circleDef = new b2CircleDef();
			
			circleDef.radius = 15;
			circleDef.density = 0.05;
			circleDef.friction = 0.5;
			circleDef.restitution = 0.7;
			circleDef.categoryBits = 0x0002;
			bodyDef.AddShape(circleDef);
			
			bodyDef.position.x = 500;
			bodyDef.position.y = 50;
			bodyDef.userData = this;
			
			userData = new object_ball();
			userData.x = x;
			userData.y = y;
			userData.width = circleDef.radius * 2; 
			userData.height = circleDef.radius * 2; 

			//bodyDef.linearDamping = 0.05;
    		//bodyDef.angularDamping = 0.1;
			//bodyDef.rotation = 10;
		}
		
	}
}













