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
	
	public class BWeaponGun extends BWeapon
	{
		public function create(x:int, y:int, scale:Boolean)
		{
			bodyDef = new b2BodyDef();
			var polyDef = new b2PolyDef();
			
			polyDef.vertexCount = 6;
			polyDef.vertices[0].Set(0,3);
			polyDef.vertices[1].Set(13,1);
			polyDef.vertices[2].Set(39,3);
			polyDef.vertices[3].Set(40,13);
			polyDef.vertices[4].Set(22,18);
			polyDef.vertices[5].Set(0,12);;
			polyDef.density = 0.3;
			polyDef.friction = 0.3;
			polyDef.restitution = 0.1;
			//polyDef.maskBits = 0x0004;
			polyDef.categoryBits = 0x0004;
			bodyDef.AddShape(polyDef);
			
			bodyDef.position.x = x;
			bodyDef.position.y = y;
			bodyDef.userData = this;
			bodyDef.allowSleep = true;
			
			if(direction==1)
			{
				change_carry_direction();
			}
		}
		
		public function BWeaponGun(x:int, y:int)
		{
			create(x,y,false);
			
			userData = new object_weaponGun();
			//userData.x = 585;
			//userData.y = 40;s
			userData.width = 40;
			userData.height = 19;
			
			
			blobbyX_draw = 3;
			blobbyY_draw = 3;
			
			blobbyX_rotate = 3;
			blobbyY_rotate = 3;
			
			load_max_time = 200;
			power = 50;
			type = "BWeaponGun";
			
			direction = 0;
		}
		
		public function shoot(test_blobby:BBlobby, tmp_calcVec:b2Vec2, m_world:b2World, rotation:Number, carry_rotation:Number):*
		{
			var test_moniTest:BMonitionGun = new BMonitionGun(test_blobby.body.m_position.x , test_blobby.body.m_position.y);
			test_moniTest.body=m_world.CreateBody(test_moniTest.bodyDef);
			test_moniTest.body.m_linearVelocity = tmp_calcVec;
			test_moniTest.body.m_linearVelocity.x *= power * test_moniTest.body.m_mass;
			test_moniTest.body.m_linearVelocity.y *= power * test_moniTest.body.m_mass;
			test_moniTest.body.m_rotation = rotation + carry_rotation;
			
			return test_moniTest;
		}		
	}
}













