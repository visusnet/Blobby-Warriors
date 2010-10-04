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
	
	public class BMonitionGun extends BMonition
	{
		// Attributes
		public var circleDef:b2CircleDef;
		
		
		public function BMonitionGun(p:BGame, x:int, y:int, ttl:int, groupIndex:int)
		{
			parent = p;
			var phy_scale:Number = parent.config.phy_scaling;
			
			
			bodyDef = new b2BodyDef();
			
			circleDef = new b2CircleDef();
			circleDef.radius = 3 / phy_scale;
			circleDef.density = 1;
			circleDef.friction = 0.5;
			//circleDef.restitution = 0.7;
			circleDef.filter.categoryBits = parent.config.categoryBits_bmonitiongun;
			circleDef.filter.maskBits = parent.config.maskBits_bmonitiongun;
			circleDef.filter.groupIndex = groupIndex;
			
			bodyDef.position.x = x / phy_scale;
			bodyDef.position.y = y / phy_scale;
			bodyDef.userData = this;
			//bodyDef.isBullet = true;
			
			userData = new object_monitionGun();
			userData.width = circleDef.radius * 2; 
			userData.height = circleDef.radius * 2;
			
			
			// TTL
			this.ttl_creationTime = getTimer();
			this.ttl_timeToLive = ttl;
			
			// etc
			type = "BMonitionGun";
			mass = 2.1;
			damage = 10;
			
			
			shapeDef = circleDef;
		}
	}
}













