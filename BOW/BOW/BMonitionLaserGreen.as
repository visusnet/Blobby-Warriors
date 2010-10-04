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
	
	public class BMonitionLaserGreen extends BMonition
	{
		// Attributes
		public var boxDef:b2PolygonDef;
		
		
		public function BMonitionLaserGreen(p:BGame, x:int, y:int, ttl:int, groupIndex:int)
		{
			parent = p;
			var phy_scale:Number = parent.config.phy_scaling;
			
			bodyDef = new b2BodyDef();
			
			boxDef = new b2PolygonDef();
			boxDef.SetAsBox(8 / phy_scale, 3 / phy_scale);
			boxDef.density = 1;
			boxDef.friction = 0.5;
			boxDef.filter.categoryBits = parent.config.categoryBits_bmonitionlasergreen;
			boxDef.filter.maskBits = parent.config.maskBits_bmonitionlasergreen;
			boxDef.filter.groupIndex = groupIndex;
			
			/*circleDef = new b2CircleDef();
			circleDef.radius = 3 / phy_scale;
			circleDef.density = 1;
			circleDef.friction = 0.5;
			//circleDef.restitution = 0.7;
			circleDef.filter.categoryBits = parent.config.categoryBits_bmonitiongun;
			circleDef.filter.maskBits = parent.config.maskBits_bmonitiongun;
			circleDef.filter.groupIndex = groupIndex;*/
			
			
			bodyDef.position.x = x/ phy_scale;
			bodyDef.position.y = y/ phy_scale;
			bodyDef.userData = this;
			//bodyDef.isBullet = true;
			
			//bodyDef.fixedRotation=true;
			
			userData = new object_monitionLaserGreen();
			userData.width = 10; 
			userData.height = 5;
			
			
			// TTL
			this.ttl_creationTime = getTimer();
			this.ttl_timeToLive = ttl;
			
			// etc
			type = "BMonitionLaserGreen";
			mass = 3;
			damage = 15;

			
			shapeDef = boxDef;
		}
	}
}













