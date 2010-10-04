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
		
		
		/*public function BContactListener(p:BGame)
		{
			parent = p;
			trace("lol");
		}*/
		
		public override function Add(point:b2ContactPoint) : void
		{
			var body1:b2Body = point.shape2.GetBody();
			
			if(body1.m_userData.type=="BBlobby" || body1.m_userData.type=="BMonitionGun" || body1.m_userData.type=="BMonitionLaserGreen")
			{
				body1.m_userData.contactListener("add", point);
				
				
			}
		}
		
		/*public override function Persist(point:b2ContactPoint) : void
		{
			trace("Persist");
		}*/
		
		public override function Remove(point:b2ContactPoint) : void
		{
			var body1:b2Body = point.shape2.GetBody();
			
			if(body1.m_userData.type=="BBlobby")
			{
				body1.m_userData.contactListener("remove", point);
				
				//parent.level.m_world.DestroyBody(body1);
				
			}
		}
		
		/*public function Result(point:b2ContactResult) : void{};
		{
			trace("Result");
		}*/
	}
}













