package
{
	// Zip
	import deng.fzip.FZip;
	import deng.fzip.FZipFile;
	import deng.utils.ChecksumUtil;

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
		public var name:String;
		public var gravity:Number;
		
		// Physic
		public var m_world:b2World;
		public var m_iterations:int = 10;
		
		// Grafik
		public var m_sprite_debug:Sprite;
		
		private var tmp_ball:BBall;
		public var tmp_blobby:BBlobby;
		public var tmp_blobby2:BBlobby;
		private var tmp_groundline:BGroundLine;
		private var tmp_weaponGun:BWeaponGun;
		private var tmp_weaponLaserGreen:BWeaponLaserGreen;
		public var tmp_crate:BCrate;
		private var tmp_blobby1:BBlobby1;
		private var tmp_image:BImage;
		private var tmp_waypoint:BWaypoint;

		// player
		public var player:*;
		
		// Images
		public var images:Array = new Array();
		
		// Destroy Bodies
		public var destroy_bodies:Array = new Array();
		
		
		public var game_type:int = 0;	// all against me^^
		public var player_array:Array = new Array();
		
		
		// Zip
		private var zip:FZip;

		// Waypoints
		public var waypoint_array:Array = new Array();
		
		public var width:int;
		public var height:int;
	
		
		var tmp_xml:XML = <level name='huhu' gravity='40'>
	<object type='BBlobby' posx='2300' posy='900' rotation='0' ki='666' content='255,255,255'></object>
	<object type='BWeaponLaserGreen' posx='440' posy='550' rotation='0' ki='-1' content='255,255,255'></object>
	<object type='BBlobby' posx='600' posy='500.00000000000006' rotation='0' ki='666' content='255,255,255'></object>
	<object type='BWeaponGun' posx='1100' posy='900' rotation='0' ki='-1' content='255,255,255'></object>
	<object type='BBlobby' posx='1100' posy='1000.0000000000001' rotation='0' ki='-1' content='255,255,255'></object>
	<object type='BWeaponLaserGreen' posx='440' posy='440.0000000000001' rotation='0' ki='-1' content='255,255,255'></object>
	<object type='BBall' posx='2300' posy='800.00000000000006' rotation='0' ki='-1' content=''></object>
	<object type='BCrate' posx='575' posy='500.00000000000006' rotation='0' ki='-1' content=''></object>
	<object type='BCrate' posx='600' posy='500.00000000000006' rotation='0' ki='-1' content=''></object>
	<object type='BCrate' posx='600' posy='500.00000000000006' rotation='0' ki='-1' content=''></object>
	
	
	<ground_line x1='386' y1='682' x2='446' y2='774' friction='1'></ground_line>
	<ground_line x1='338' y1='557' x2='386' y2='682' friction='1'></ground_line>
	<ground_line x1='324' y1='420' x2='338' y2='557' friction='1'></ground_line>
	<ground_line x1='678' y1='473' x2='324' y2='420' friction='1'></ground_line>
	<ground_line x1='973' y1='425' x2='678' y2='473' friction='1'></ground_line>
	<ground_line x1='1054' y1='485' x2='973' y2='425' friction='1'></ground_line>
	<ground_line x1='1093' y1='560' x2='1054' y2='485' friction='1'></ground_line>
	<ground_line x1='1248' y1='500' x2='1093' y2='560' friction='1'></ground_line>
	<ground_line x1='1342' y1='662' x2='1248' y2='500' friction='1'></ground_line>
	<ground_line x1='1334' y1='858' x2='1342' y2='662' friction='1'></ground_line>
	<ground_line x1='1400' y1='900' x2='1334' y2='858' friction='1'></ground_line>
	<ground_line x1='1547' y1='844' x2='1400' y2='900' friction='1'></ground_line>
	<ground_line x1='1612' y1='892' x2='1547' y2='844' friction='1'></ground_line>
	<ground_line x1='1718' y1='688' x2='1612' y2='892' friction='1'></ground_line>
	<ground_line x1='1680' y1='550' x2='1718' y2='688' friction='1'></ground_line>
	<ground_line x1='1815' y1='492' x2='1680' y2='550' friction='1'></ground_line>
	<ground_line x1='2233' y1='457' x2='1815' y2='492' friction='1'></ground_line>
	<ground_line x1='2548' y1='550' x2='2233' y2='457' friction='1'></ground_line>
	<ground_line x1='2539' y1='880' x2='2548' y2='550' friction='1'></ground_line>
	<ground_line x1='2520' y1='920' x2='2539' y2='880' friction='1'></ground_line>
	<ground_line x1='2436' y1='971' x2='2520' y2='920' friction='1'></ground_line>
	<ground_line x1='2175' y1='971' x2='2436' y2='971' friction='1'></ground_line>
	<ground_line x1='2114' y1='1013' x2='2175' y2='971' friction='1'></ground_line>
	<ground_line x1='2129' y1='1034' x2='2114' y2='1013' friction='1'></ground_line>
	<ground_line x1='2133' y1='1078' x2='2129' y2='1034' friction='1'></ground_line>
	<ground_line x1='2020' y1='1134' x2='2133' y2='1078' friction='1'></ground_line>
	<ground_line x1='1125' y1='1140' x2='2020' y2='1134' friction='1'></ground_line>
	<ground_line x1='1009' y1='1084' x2='1125' y2='1140' friction='1'></ground_line>
	<ground_line x1='961' y1='1041' x2='1009' y2='1084' friction='1'></ground_line>
	<ground_line x1='895' y1='933' x2='961' y2='1041' friction='1'></ground_line>
	<ground_line x1='762' y1='933' x2='895' y2='933' friction='1'></ground_line>
	<ground_line x1='740' y1='920' x2='762' y2='933' friction='1'></ground_line>
	<ground_line x1='740' y1='832' x2='740' y2='920' friction='1'></ground_line>
	<ground_line x1='687' y1='774' x2='740' y2='832' friction='1'></ground_line>
	<ground_line x1='446' y1='774' x2='687' y2='774' friction='1'></ground_line>
	

	
	
	<image posx='59' posy='0' src='6.jpg' rotation='0' layer='-6'></image>
	<image posx='1999' posy='0' src='5.jpg' rotation='0' layer='-6'></image>
	<image posx='59' posy='-250' src='4.jpg' rotation='0' layer='-2'></image>
	<image posx='1999' posy='-250' src='3.jpg' rotation='0' layer='-2'></image>
	<image posx='0' posy='0' src='2.jpg' rotation='0' layer='1'></image>
	<image posx='1999' posy='0' src='1.jpg' rotation='0' layer='1'></image>
	
	
	
	<waypoint id='0' posx='450' posy='750'>
		<waypoint_con_id id='1'></waypoint_con_id>
	</waypoint>
	
	<waypoint id='1' posx='650' posy='750'>
		<waypoint_con_id id='0'></waypoint_con_id>
		<waypoint_con_id id='2'></waypoint_con_id>
	</waypoint>
	
	<waypoint id='2' posx='750' posy='800'>
		<waypoint_con_id id='1'></waypoint_con_id>
		<waypoint_con_id id='3'></waypoint_con_id>
	</waypoint>
	
	<waypoint id='3' posx='830' posy='900'>
		<waypoint_con_id id='2'></waypoint_con_id>
		<waypoint_con_id id='4'></waypoint_con_id>
	</waypoint>
	
	<waypoint id='4' posx='880' posy='900'>
		<waypoint_con_id id='3'></waypoint_con_id>
		<waypoint_con_id id='5'></waypoint_con_id>
	</waypoint>
	
	<waypoint id='5' posx='950' posy='1000'>
		<waypoint_con_id id='4'></waypoint_con_id>
		<waypoint_con_id id='6'></waypoint_con_id>
	</waypoint>
	
	<waypoint id='6' posx='1100' posy='1110'>
		<waypoint_con_id id='5'></waypoint_con_id>
		<waypoint_con_id id='7'></waypoint_con_id>
	</waypoint>
	
	<waypoint id='7' posx='1250' posy='1120'>
		<waypoint_con_id id='6'></waypoint_con_id>
		<waypoint_con_id id='8'></waypoint_con_id>
	</waypoint>
	
	<waypoint id='8' posx='1500' posy='1120'>
		<waypoint_con_id id='7'></waypoint_con_id>
		<waypoint_con_id id='9'></waypoint_con_id>
	</waypoint>
	
	<waypoint id='9' posx='1700' posy='1120'>
		<waypoint_con_id id='8'></waypoint_con_id>
		<waypoint_con_id id='10'></waypoint_con_id>
	</waypoint>
	
	<waypoint id='10' posx='1900' posy='1120'>
		<waypoint_con_id id='9'></waypoint_con_id>
		<waypoint_con_id id='11'></waypoint_con_id>
	</waypoint>
	
	<waypoint id='11' posx='2120' posy='980'>
		<waypoint_con_id id='10'></waypoint_con_id>
		<waypoint_con_id id='12'></waypoint_con_id>
	</waypoint>
	
	<waypoint id='12' posx='2300' posy='955'>
		<waypoint_con_id id='11'></waypoint_con_id>
	</waypoint>
	


</level>
		
		

		
		// ERWEITERN! nur sichbare waypoints...
		public function get_newest_waypoint(pos:b2Vec2) : int
		{
			var shortest_distance:Array = new Array(-1,-1);
			
			for each(var tmp_wp:BWaypoint in waypoint_array)
			{
				var a:Number = tmp_wp.posx - pos.x;
				var b:Number = tmp_wp.posy - pos.y;
				var tmp_distance = Math.sqrt((a*a) + (b*b));
				
				if(tmp_distance<shortest_distance[0] || shortest_distance[0] == -1)
				{
					shortest_distance[0] = tmp_distance;
					shortest_distance[1] = tmp_wp.id;
				}
			}
			
			return shortest_distance[1];
		}
		
		
		public function get_waypoint(id:int) : BWaypoint
		{
			for each(var Bwp:BWaypoint in waypoint_array)
				if(Bwp.id == id)
					return Bwp;
			
			return null;			
		}
		
		public function get_free_waypoint_id() : int
		{
			for(var i:int = 0; i < parent.config.max_waypoints; i++)
				if(get_waypoint(i) == null)
					return i;
					
			return -1;
		}
		
		
		
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
					if(bb.GetUserData()!=null)
						if(bb.GetUserData().type=="BBlobby")
							bb.GetUserData().destroy();
							
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
			var xml_string:String;
			
			
			xml_string = "<level name='" + name + "' gravity='" + gravity + "' width='" + width + "' height='" + height + "'>\n";
			
			
			// alle Bodies durchgehen und XML-String generieren
			for (var bb:b2Body = m_world.m_bodyList; bb; bb = bb.m_next)
			{
				if (bb.GetUserData() != null)
				{
					if(bb.GetUserData().type == "BGroundLine" ||
						bb.GetUserData().type == "BBall" ||
						bb.GetUserData().type == "BCrate" ||
						bb.GetUserData().type == "BWeaponGun" ||
						bb.GetUserData().type == "BWeaponLaserGreen")
						xml_string += "\t" + bb.GetUserData().toXML() + "\n";
				}
			}
			
			
			// alle Images durchgehen und XML-String generieren
			for each (var img:BImage in images)
			{
				xml_string += "\t" + img.toXML() + "\n";
			}
			
			// alle Waypoints durchgehen und XML-String generieren
			for each (var wayp:BWaypoint in waypoint_array)
			{
				xml_string += "\t" + wayp.toXML() + "\n";
			}
			
			
			// ende
			xml_string += "</level>";
			
			
			trace(xml_string);
		}
		
		private function create_world()
		{
			// world-object
			var worldAABB:b2AABB = new b2AABB();
			worldAABB.lowerBound.Set(-2000.0, -2000.0);
			worldAABB.upperBound.Set(2000.0, 2000.0);

			gravity = 600 / parent.config.phy_scaling;
			//gravity = 0;
			
			//var gravity_vec:b2Vec2 = new b2Vec2(0.0, 0.0);
			var gravity_vec:b2Vec2 = new b2Vec2(0.0, gravity);
			var doSleep:Boolean = true;
			m_world = new b2World(worldAABB, gravity_vec, doSleep);

						
			// init debug draw
			m_sprite_debug = new Sprite();
			
			var dbgDraw:b2DebugDraw = new b2DebugDraw();
			dbgDraw.m_sprite = m_sprite_debug;
			dbgDraw.m_drawScale = parent.config.phy_scaling;
			dbgDraw.m_fillAlpha = 0.3;
			
			dbgDraw.m_lineThickness = 1.0;
			dbgDraw.m_drawFlags = b2DebugDraw.e_shapeBit | b2DebugDraw.e_jointBit | b2DebugDraw.e_coreShapeBit | b2DebugDraw.e_aabbBit | b2DebugDraw.e_obbBit | b2DebugDraw.e_pairBit | b2DebugDraw.e_centerOfMassBit;
			//dbgDraw.m_drawFlags = b2DebugDraw.e_shapeBit | b2DebugDraw.e_centerOfMassBit;
			//dbgDraw.m_drawFlags = b2DebugDraw.e_shapeBit;
			//m_world.SetDebugDraw(dbgDraw);
			
			
			// Listeners
			m_world.SetContactListener(parent.contactListener);
			m_world.SetBoundaryListener(parent.boundaryListener);
		}
		
		public function parseXML(xml_string:String)
		{
			// XMLDocument
			var result:XMLDocument = new XMLDocument();
            result.ignoreWhite = true;
            result.parseXML(xml_string);
			
			
			// firstNode / World
			name = result.firstChild.attributes.name;
			gravity = result.firstChild.attributes.gravity;
			width = result.firstChild.attributes.width;
			height = result.firstChild.attributes.height;
			create_world();
			

			// alle nodes durchgehen und objecte/images/grounds erstellen
			for each(var node:XMLNode in result.firstChild.childNodes)
			{
                switch(node.nodeName)
				{
					// waypoint
					case "waypoint":
						var tmp_array:Array = new Array(10);
						
						// connected waypoints
						for each(var node_cwp:XMLNode in node.childNodes)
							tmp_array.push(new Array(node_cwp.attributes.id, 10));
						
						tmp_waypoint = new BWaypoint(node.attributes.id, node.attributes.posx, node.attributes.posy, tmp_array);
						
						waypoint_array.push(tmp_waypoint);
					break;
					
					
					// object
					case "object":
						switch(node.attributes.type)
						{
							// BCrate
							case "BCrate":
								tmp_crate = new BCrate(parent, node.attributes.posx, node.attributes.posy);
								tmp_crate.add();
							break;
							
							// BWeaponGun
							case "BWeaponGun":
								tmp_weaponGun = new BWeaponGun(parent, node.attributes.posx, node.attributes.posy);
								tmp_weaponGun.add();
							break;
							
							// BWeaponLaserGreen
							case "BWeaponLaserGreen":
								tmp_weaponLaserGreen = new BWeaponLaserGreen(parent, node.attributes.posx, node.attributes.posy);
								tmp_weaponLaserGreen.add();
							break;
							
							// BBall
							case "BBall":
								tmp_ball = new BBall(parent, node.attributes.posx, node.attributes.posy);
								tmp_ball.add();
							break;
							
							// default
							default:
							break;
						}
					break;
					
					// ground_line
					case "ground_line":
						tmp_groundline = new BGroundLine(parent, new Point(node.attributes.x1,node.attributes.y1),new Point(node.attributes.x2,node.attributes.y2),node.attributes.friction);
						tmp_groundline.add();
					break;
					
					// image
					case "image":
						var img_file:FZipFile = zip.getFileByName(node.attributes.src);
			
						if(img_file != null)
						{

							tmp_image = new BImage(parent, node.attributes.src, node.attributes.posx, node.attributes.posy, node.attributes.rotation, node.attributes.layer);

							tmp_image.loader = new Loader();
							tmp_image.loader.contentLoaderInfo.addEventListener(Event.COMPLETE, tmp_image.onImageLoadComplete);
							tmp_image.loader.contentLoaderInfo.addEventListener(IOErrorEvent.IO_ERROR, tmp_image.onImageLoadError);
							tmp_image.loader.contentLoaderInfo.addEventListener(ProgressEvent.PROGRESS , tmp_image.progressHandler);

							tmp_image.loader.loadBytes(img_file.content);
						}
						else
						{
							trace("fehler");
						}
					break;
					
					// default
					default: 
					break;
				}
            }

		}
		

		
		public function logic()
		{
			// genug spieler vorhanden?
			if(player_array.length < 2)
			{
				
				
				if(player==null)
				{
					tmp_blobby = new BBlobby(parent, 350, 400);
					tmp_blobby.add();
				
					player = tmp_blobby as BBlobby;
				}
				else
				{
					tmp_blobby2 = new BBlobby(parent, 400, 400);
					tmp_blobby2.add();
					
					var tmp_player:BPlayer = new BPlayer(tmp_blobby2);
					player_array.push(tmp_player);
									
					var tmp_ki:BKI = new BKI(parent, tmp_blobby2.body);
					
					return;
				}
				
				var tmp_player:BPlayer = new BPlayer(tmp_blobby);
				player_array.push(tmp_player);
			}
			
			// spieler tot? wenn ja... wiederbeleben
			for each(var pl:BPlayer in player_array)
			{
				if(pl.object.health <= 0 && (getTimer() - pl.dead_time) > 5000 && pl.dead_time != 0)
				{
					pl.object.create(500, 500);
					pl.object.add();
					pl.dead_time = 0;
				}
			}
			
			
		}
		
		private function onOpen(evt:Event)
		{
			trace(getTimer() + " geöffnet!");
		}
		
		private function onComplete(evt:Event)
		{
			trace(getTimer() + " fertig!");
			
			check_zip_content();
			
			
			// player erstellen
			/*tmp_blobby = new BBlobby(parent, 500, 500);
			tmp_blobby.add();
			
			player = tmp_blobby as BBlobby;
			
			var tmp_player:BPlayer = new BPlayer(tmp_blobby);
			player_array.push(tmp_player);
			
			
			// zu den anderen clients senden
			var buf:String = "new_player" + ";" + tmp_blobby.id + ";" + "500" + ";" + "500";
			parent.sendMessage(buf);*/
		}
		
		private function check_zip_content()
		{
			// Level-File laden
			var file:FZipFile = zip.getFileByName("level.xml");
			
			if(file != null)
			{
				parseXML(file.content.toString());
			}
			else
			{
				trace("Error loading File");
				return;
			}
			

			
			// Level im parent starten
			// MCs
			parent.addChild(m_sprite_debug);
			
			
			// erst weitermachen wenne alle Bilder geladen sind
			var found:Boolean = false;
			do
			{
				for each(var img:BImage in images)
				{
					if(img.loadComplete == false)
						found = true;
				}
			}
			while(found == true);
			
			
			
			var count:int = 0;
			var amount:int = 0;
			for (var bb:b2Body = m_world.m_bodyList; bb; bb = bb.m_next)
			{
				if (bb.GetUserData() != null)
				{
					if(bb.GetUserData().type == "BGroundLine")
					{
						var a:Number = bb.GetUserData().p1.x - bb.GetUserData().p2.x;
						var b:Number = bb.GetUserData().p1.y - bb.GetUserData().p2.y;
						var c:Number = Math.sqrt((a*a) + (b*b));
															   
						count++;
						amount += c;
					}
				}
			}
			
			
			/*trace(getTimer() + " count: " + count);
			trace(getTimer() + " amount: " + amount);
			trace(getTimer() + " count/amount: " + amount/count);*/
			
			


			
			// Events
			parent.updateNow = getTimer();
			parent.updateLast = getTimer();
			parent.addEventListener(Event.ENTER_FRAME, parent.update, false, 0, true);
		}

		public function load(level:String)
		{
			// Load Zip-Level file
			zip = new FZip();
			zip.addEventListener(Event.OPEN, onOpen);
			zip.addEventListener(Event.COMPLETE, onComplete);
			//zip.load(new URLRequest("http://bow.babeltech.de/maps/test.zip"));
			zip.load(new URLRequest("maps/" + level + ".zip"));
		}
	}
}
