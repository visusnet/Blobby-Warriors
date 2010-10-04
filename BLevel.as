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
	import flash.xml.*;
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
	
	public class BLevel
	{
		// ### Atributes ###
		public var parent:BGame;
		
		// Physic
		public var m_world:b2World;
		public var m_iterations:int = 10;
		
		// Grafik
		public var m_sprite_debug:Sprite;
		
		// Background
		var backGroundBD:BitmapData;
		var backGround:background;
		
		public var test_ball:BBall;
		public var test_blobby:BBlobby;
		public var test_groundline:BGroundLine;
		public var test_weaponGun:BWeaponGun;
		public var test_weaponLaserGreen:BWeaponLaserGreen;
		public var test_crate:BCrate;
		public var test_palme:palme;
		
		// player
		public var player:*;
		
		// Images
		public var images:Array;
		
		// Destroy Bodies
		public var destroy_bodies:Array;
		
		
		public function BLevel(p:BGame)
		{
			parent = p;
		}
		
		public function destroy_body(clean:Boolean, body:b2Body)
		{
			if(clean==true)
			{
				for each (var bb:b2Body in destroy_bodies )
				{
					m_world.DestroyBody(bb);
				}
				
				destroy_bodies = new Array();
			}
			else
			{
				destroy_bodies.push(body);
			}
		}
		
		public function save()
		{
			
			var xml_doc:XMLDocument;
			xml_doc = new XMLDocument("");
			
			var tmp_node:XMLNode = xml_doc.createElement("object");
			var tmp_node:XMLNode = xml_doc.createElement("object");
			
			
			xml_doc.appendChild(tmp_node);

			
			
			var myXML:XML = <level name="Testlevel" gravity="9.81" />;
			myXML.appendChild(tmp_node);
			
			trace(myXML.toString());
		}
		
		public function load(name:String)
		{
			//save();
			
			// Creat world AABB
			var worldAABB:b2AABB = new b2AABB();
			worldAABB.lowerBound.Set(-2000.0, -2000.0);
			worldAABB.upperBound.Set(2000.0, 2000.0);

			var gravity:b2Vec2 = new b2Vec2(0.0, 40.0);
			var doSleep:Boolean = true;
			m_world = new b2World(worldAABB, gravity, doSleep);

						
			// init debug draw
			m_sprite_debug = new Sprite();
			
			var dbgDraw:b2DebugDraw = new b2DebugDraw();
			dbgDraw.m_sprite = m_sprite_debug;
			dbgDraw.m_drawScale = parent.config.phy_scaling;
			dbgDraw.m_fillAlpha = 0.3;
			dbgDraw.m_lineThickness = 1.0;
			//dbgDraw.m_drawFlags = b2DebugDraw.e_shapeBit | b2DebugDraw.e_jointBit;
			dbgDraw.m_drawFlags = b2DebugDraw.e_shapeBit;
			m_world.SetDebugDraw(dbgDraw);

			
			
			// images
			images = new Array();
			
			
			// destroy_bodies
			destroy_bodies = new Array();
			

			backGround = new background();
			backGroundBD = new BitmapData(1000,600,true,0x00000000);
			backGroundBD.draw(backGround, new Matrix());
			//parent.addChild(backGround);
			
			
			test_groundline = new BGroundLine(parent, 200,100, 100, 0);
			test_groundline.add();
			
			test_groundline = new BGroundLine(parent, 150,200, 100, 0);
			test_groundline.add();

			test_groundline = new BGroundLine(parent, 200,400, 100, 0);
			test_groundline.add();
			
			test_groundline = new BGroundLine(parent, 200,600, 100, 0);
			test_groundline.add();
			
			test_groundline = new BGroundLine(parent, 200,800, 100, 0);
			test_groundline.add();
		
			

			test_groundline = new BGroundLine(parent, 400,700, 100, 0);
			test_groundline.add();
			
			test_groundline = new BGroundLine(parent, 600,700, 100, 40);
			test_groundline.add();
			
			test_groundline = new BGroundLine(parent, 800,700, 100, 0);
			test_groundline.add();
			
			test_groundline = new BGroundLine(parent, 1000,700, 100, 0);
			test_groundline.add();
			
			
			
			test_groundline = new BGroundLine(parent, 1050,750, 100, 0);
			test_groundline.add();
			
			test_groundline = new BGroundLine(parent, 1100,800, 100, 0);
			test_groundline.add();
			
			test_groundline = new BGroundLine(parent, 1150,850, 100, 0);
			test_groundline.add();
			
			test_groundline = new BGroundLine(parent, 1200,900, 100, 0);
			test_groundline.add();
			
			test_groundline = new BGroundLine(parent, 1250,950, 100, 0);
			test_groundline.add();
			
			test_groundline = new BGroundLine(parent, 1300,1000, 100, 0);
			test_groundline.add();
			
			test_groundline = new BGroundLine(parent, 1400,1000, 100, 0);
			test_groundline.add();
			
			test_groundline = new BGroundLine(parent, 1500,1000, 100, 0);
			test_groundline.add();
			
			test_groundline = new BGroundLine(parent, 1600,1000, 100, 0);
			test_groundline.add();
			
			test_groundline = new BGroundLine(parent, 1700,1000, 100, 0);
			test_groundline.add();
			
			test_groundline = new BGroundLine(parent, 1800,1000, 100, 0);
			test_groundline.add();
			
			
			test_groundline = new BGroundLine(parent, 1800,900, 100, 0);
			test_groundline.add();
			
			test_groundline = new BGroundLine(parent, 1800,800, 100, 0);
			test_groundline.add();
			
			test_groundline = new BGroundLine(parent, 1800,700, 100, 0);
			test_groundline.add();
			
			test_groundline = new BGroundLine(parent, 1800,600, 100, 0);
			test_groundline.add();
			
			test_groundline = new BGroundLine(parent, 1800,500, 100, 0);
			test_groundline.add();
			
			test_groundline = new BGroundLine(parent, 1800,400, 100, 0);
			test_groundline.add();
			
			test_groundline = new BGroundLine(parent, 1800,300, 100, 0);
			test_groundline.add();

			
			


			test_crate = new BCrate(parent, 600,600);
			test_crate.add();

			test_crate = new BCrate(parent, 600,550);
			test_crate.add();
			
			test_crate = new BCrate(parent, 575,600);
			test_crate.add();
			
			
			test_crate = new BCrate(parent, 1100,650);
			test_crate.add();
			
			test_crate = new BCrate(parent, 1100,630);
			test_crate.add();
			
			test_crate = new BCrate(parent, 1100,610);
			test_crate.add();
			
			test_crate = new BCrate(parent, 1090,610);
			test_crate.add();
			
			test_crate = new BCrate(parent, 400, 50);
			test_crate.add();

			test_crate = new BCrate(parent, 400, 50);
			test_crate.add();
			

			test_ball = new BBall(parent, 500, 50);
			test_ball.add();

			test_blobby = new BBlobby(parent, 700,40);
			test_blobby.add();
			player = test_blobby;
			

			

			var img:BImage = new BImage(parent, new palme(), 1050, 537, 0);
			images.push(img);
			
			
			img = new BImage(parent, new palme(), 800, 537, 0);
			images.push(img);
			

			

			test_weaponGun = new BWeaponGun(parent, 750,600);
			test_weaponGun.add();
			
			test_weaponLaserGreen = new BWeaponLaserGreen(parent, 440,265);
			test_weaponLaserGreen.add();
			
			
			// add debug draw sprite
			//parent.addChild(m_sprite_debug);
		}
	}
}













