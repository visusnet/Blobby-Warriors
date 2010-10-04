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
	
	public class BContactListener extends b2ContactListener
	{
		// ### Atributes ###
		public var parent:BGame;

		
		public override function Add(point:b2ContactPoint) : void
		{
			var body1:b2Body = point.shape1.GetBody();
			var body2:b2Body = point.shape2.GetBody();
			
			if(body1.GetUserData() == null || body2.GetUserData() == null)
				return;
			
			if(body1.GetUserData().type=="BBlobby" || body1.GetUserData().type=="BMonitionGun" || body1.GetUserData().type=="BMonitionLaserGreen")
			{
				body1.GetUserData().contactListener("add", point, true);
			}
			
			if(body2.GetUserData().type=="BBlobby" || body2.GetUserData().type=="BMonitionGun" || body2.GetUserData().type=="BMonitionLaserGreen")
			{
				body2.GetUserData().contactListener("add", point, false);
			}
		}
		
		public override function Persist(point:b2ContactPoint) : void
		{
			var body1:b2Body = point.shape1.GetBody();
			var body2:b2Body = point.shape2.GetBody();
			
			if(body1.GetUserData() == null || body2.GetUserData() == null)
				return;
				
				
			if(body1.GetUserData().type=="BBlobby" || body1.GetUserData().type=="BMonitionGun" || body1.GetUserData().type=="BMonitionLaserGreen")
			{
				body1.GetUserData().contactListener("add", point, true);
			}
			
			if(body2.GetUserData().type=="BBlobby" || body2.GetUserData().type=="BMonitionGun" || body2.GetUserData().type=="BMonitionLaserGreen")
			{
				body2.GetUserData().contactListener("add", point, false);
			}
		}
		
		public override function Remove(point:b2ContactPoint) : void
		{
			var body1:b2Body = point.shape1.GetBody();
			var body2:b2Body = point.shape2.GetBody();
			
			if(body1.GetUserData() == null || body2.GetUserData() == null)
				return;
				
			
			if(body1.GetUserData().type=="BBlobby")
			{
				body1.GetUserData().contactListener("remove", point, true);
			}
			
			if(body2.GetUserData().type=="BBlobby")
			{
				body2.GetUserData().contactListener("remove", point, false);
			}
		}
		
		/*public function Result(point:b2ContactResult) : void{};
		{
			trace("Result");
		}*/
	}
}













