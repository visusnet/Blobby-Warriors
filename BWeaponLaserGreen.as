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
	import flash.geom.*;
	
	public class BWeaponLaserGreen extends BWeapon
	{
		public function create(x:int, y:int,scale:Boolean)
		{
			var phy_scale:Number = parent.config.phy_scaling;
			
			
			bodyDef = new b2BodyDef();
			polyDef = new b2PolygonDef();
			
			/*polyDef.vertexCount = 4;
			polyDef.vertices[0].Set(1 / phy_scale,0 / phy_scale);
			polyDef.vertices[1].Set(35 / phy_scale,0 / phy_scale);
			polyDef.vertices[2].Set(48 / phy_scale,6 / phy_scale);
			polyDef.vertices[3].Set(8 / phy_scale,18 / phy_scale);*/
			
			polyDef.vertexCount = 4;
			polyDef.vertices[0].Set(1 / phy_scale,0 / phy_scale);
			polyDef.vertices[1].Set(35 / phy_scale,0 / phy_scale);
			polyDef.vertices[2].Set(48 / phy_scale,6 / phy_scale);
			polyDef.vertices[3].Set(8 / phy_scale,18 / phy_scale);
				
			if(direction==1)
			{
				change_carry_direction();
			}

			polyDef.density = 0.3;
			polyDef.friction = 0.3;
			polyDef.restitution = 0.1;
			polyDef.filter.categoryBits = parent.config.categoryBits_bweaponlasergreen;
			polyDef.filter.maskBits = parent.config.maskBits_bweaponlasergreen;
			
			bodyDef.position.x = x / phy_scale;
			bodyDef.position.y = y / phy_scale;
			bodyDef.userData = this;
			bodyDef.allowSleep = true;
		}
		
		public function BWeaponLaserGreen(p:BGame, x:int, y:int)
		{
			parent = p;
			
			create(x,y,false);
			
			// userdate
			userData = new object_weaponLaserGreen();
			userData.width = 40;
			userData.height = 19;
			

			// bdraw
			trans_x = 50/2;
			trans_y = 20/2;
			trans_x2 = 15;
			trans_y2 = 30;
			trans_BD_width = 80;
			trans_BD_height = 80;
			trans_x_carry = 40;
			trans_y_carry = 17;
			trans_x_move = 4;
			trans_x_move_left = 0;
			trans_y_move = 7;
			carry_middle_x = 5;
			carry_middle_x_left = -2;
			carry_middle_y = 4;
			
			// etc
			load_max_time = 400;
			type = "BWeaponLaserGreen";
			power = 250;
			mass = 9.5;
			ttl = -1;
			pos = 2;
			
			direction = 0;
			
			sound = new WeaponLaserGreen0();
		}
		
		public function shoot(carry_rotation:Number)
		{
			// sound
			if(parent.config.sound == true)
				sound.play();
			
			
			var tmp_x:Number = carrier.GetWorldCenter().x+(carry_middle_x/parent.config.phy_scaling);
			var tmp_y:Number = carrier.GetWorldCenter().y+(carry_middle_y/parent.config.phy_scaling);
			
			tmp_y += getWeaponMovementFromCurFrame()/parent.config.phy_scaling;
			
			var test_moniLaserGreen:BMonitionLaserGreen = new BMonitionLaserGreen(parent, tmp_x*parent.config.phy_scaling, tmp_y*parent.config.phy_scaling, ttl, carrier.GetUserData().groupIndex);
			
			test_moniLaserGreen.add();
			
			test_moniLaserGreen.body.m_linearVelocity = parent.rad2vec(angle + carry_rotation);
			test_moniLaserGreen.body.m_linearVelocity.x *= (power/parent.config.phy_scaling) * test_moniLaserGreen.body.GetMass();
			test_moniLaserGreen.body.m_linearVelocity.y *= (power/parent.config.phy_scaling) * test_moniLaserGreen.body.GetMass();
			//test_moniLaserGreen.body.m_linearVelocity.x += parent.level.player.body.m_linearVelocity.x;
			//test_moniLaserGreen.body.m_linearVelocity.y += parent.level.player.body.m_linearVelocity.y;
			
			test_moniLaserGreen.body.m_sweep.a = angle + carry_rotation;
		}		
	}
}













