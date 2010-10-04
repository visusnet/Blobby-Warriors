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
	
	public class BWeaponLaserGreen extends BWeapon
	{
		public function create(x:int, y:int,scale:Boolean)
		{
			bodyDef = new b2BodyDef();
			var polyDef = new b2PolyDef();
			
			polyDef.vertexCount = 4;
			polyDef.vertices[0].Set(1,0);
			polyDef.vertices[1].Set(35,0);
			polyDef.vertices[2].Set(48,6);
			polyDef.vertices[3].Set(8,18);
				
			if(direction==1)
			{
				change_carry_direction();
			}

			//polyDef.vertices[4].Set(13,11);
			//polyDef.vertices[5].Set(9,19);;
			//polyDef.vertices[6].Set(9,19);;
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
			//bodyDef.preventRotation = true;
		}
		
		public function BWeaponLaserGreen(x:int, y:int)
		{
			create(x,y,false);
			
			userData = new object_weaponLaserGreen();
			//userData.x = 585;
			//userData.y = 40;
			userData.width = 40;
			userData.height = 19;
			
			
			blobbyX_draw = 7;
			blobbyY_draw = 3;
			
			blobbyX_rotate = 120;
			blobbyY_rotate = 0;
			
			
			load_max_time = 400;
			type = "BWeaponLaserGreen";
			power = 5;
			
			direction = 0;
		}
		
		
		public function shoot(test_blobby:BBlobby, tmp_calcVec:b2Vec2, m_world:b2World, rotation:Number, carry_rotation:Number):*
		{
			var test_moniTest:BMonitionLaserGreen = new BMonitionLaserGreen(test_blobby.body.m_position.x , test_blobby.body.m_position.y);
			test_moniTest.body=m_world.CreateBody(test_moniTest.bodyDef);
			test_moniTest.body.m_linearVelocity = tmp_calcVec;
			test_moniTest.body.m_linearVelocity.x *= power * test_moniTest.body.m_mass;
			test_moniTest.body.m_linearVelocity.y *= power * test_moniTest.body.m_mass;
			test_moniTest.body.m_rotation = rotation + carry_rotation;
			
			return test_moniTest;
		}
	}
}













