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
	
	public class BWeaponGun extends BWeapon
	{
		public function create(x:int, y:int, scale:Boolean)
		{
			var phy_scale:Number = parent.config.phy_scaling;
			
			
			bodyDef = new b2BodyDef();
			polyDef = new b2PolygonDef();
			
			polyDef.vertexCount = 6;
			polyDef.vertices[0].Set(0 / phy_scale,3 / phy_scale);
			polyDef.vertices[1].Set(13 / phy_scale,1 / phy_scale);
			polyDef.vertices[2].Set(39 / phy_scale,3 / phy_scale);
			polyDef.vertices[3].Set(40 / phy_scale,13 / phy_scale);
			polyDef.vertices[4].Set(22 / phy_scale,18 / phy_scale);
			polyDef.vertices[5].Set(0 / phy_scale,12 / phy_scale);
			polyDef.density = 0.3;
			polyDef.friction = 0.3;
			polyDef.restitution = 0.1;
			polyDef.filter.categoryBits = parent.config.categoryBits_bweapongun;
			polyDef.filter.maskBits = parent.config.maskBits_bweapongun;
			
			bodyDef.position.x = x / phy_scale;
			bodyDef.position.y = y / phy_scale;
			bodyDef.userData = this;
			bodyDef.allowSleep = true;
			
			if(direction==1)
			{
				change_carry_direction();
			}
		}
		
		public function BWeaponGun(p:BGame, x:int, y:int)
		{
			parent = p;
			
			
			create(x,y,false);
			
			// userdata
			userData = new object_weaponGun();
			userData.width = 40;
			userData.height = 19;
			
			
			// bdraw
			trans_x = 40/2;
			trans_y = 19/2;
			trans_x2 = 20;
			trans_y2 = 30;
			trans_BD_width = 80;
			trans_BD_height = 80;
			trans_x_carry = 35;
			trans_y_carry = 18;
			trans_x_move = 4;
			trans_x_move_left = 0;
			trans_y_move = 7;
			carry_middle_x = 6;
			carry_middle_x_left = -2;
			carry_middle_y = 4;

			
			load_max_time = 200;
			power = 350;
			type = "BWeaponGun";
			mass = 5;
			ttl = -1;
			
			direction = 0;
			
			
			sound = new MachineGun0();
		}
		
		public function shoot(carry_rotation:Number)
		{
			// sound
			sound.play();
			
			
			var tmp_x:Number = carrier.GetWorldCenter().x+(carry_middle_x/parent.config.phy_scaling);
			var tmp_y:Number = carrier.GetWorldCenter().y+(carry_middle_y/parent.config.phy_scaling);

			tmp_y += getWeaponMovementFromCurFrame()/parent.config.phy_scaling;
			
			var test_moniGun:BMonitionGun = new BMonitionGun(parent, tmp_x*parent.config.phy_scaling, tmp_y*parent.config.phy_scaling, ttl, carrier.GetUserData().groupIndex);
			
			test_moniGun.add();
			
			test_moniGun.body.m_linearVelocity = parent.rad2vec(angle + carry_rotation);
			test_moniGun.body.m_linearVelocity.x *= (power/parent.config.phy_scaling) * test_moniGun.body.GetMass();
			test_moniGun.body.m_linearVelocity.y *= (power/parent.config.phy_scaling) * test_moniGun.body.GetMass();
			
			//test_moniGun.body.m_sweep.a = rotation + carry_rotation;
		}		
	}
}













