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
	
	public class Main extends MovieClip
	{
		// MovieClips
		var mc_game:BGame;
		var mc_mainMenue:BMainMenue = new BMainMenue();
		//var mc_playerLeiste:playerLeiste = new playerLeiste();
		//var mc_border:border = new border();

												
		
		public function Main()
		{
			// Events
			addEventListener(Event.ENTER_FRAME, update, false, 0, true);

			addChild(mc_mainMenue);
		}
		
		public function startGame()
		{
			mc_mainMenue.visible = false;			
			//mc_game.visible = true;
			
			//if(mc_game==null)
			//{
				//mc_game = new BGame();
			//}
			//else
			//	mc_game.load_level("huhu");
			
			//mc_game.load_level("huhu");
			
			
			//var InvalidBitmapData:BitmapData = new BitmapData(3000, 3000);
			
			
			
			mc_game = new BGame();
			
			stage.addEventListener(KeyboardEvent.KEY_DOWN, mc_game.event_KeyDown);
			stage.addEventListener(KeyboardEvent.KEY_UP, mc_game.event_KeyUp);
			addEventListener(MouseEvent.MOUSE_MOVE, mc_game.event_MouseMove);
			addEventListener(MouseEvent.MOUSE_DOWN, mc_game.event_MouseDown);
			addEventListener(MouseEvent.MOUSE_UP, mc_game.event_MouseUp);
			
			addChild(mc_game);
			//addChild(mc_playerLeiste);
			
			//mc_playerLeiste.y = 600-89;
			
			Mouse.hide();
		}		
		
		public function stopGame()
		{
			mc_mainMenue.visible = true;
			
			stage.removeEventListener(KeyboardEvent.KEY_DOWN, mc_game.event_KeyDown);
			stage.removeEventListener(KeyboardEvent.KEY_UP, mc_game.event_KeyUp);
			removeEventListener(MouseEvent.MOUSE_MOVE, mc_game.event_MouseMove);
			removeEventListener(MouseEvent.MOUSE_DOWN, mc_game.event_MouseDown);
			removeEventListener(MouseEvent.MOUSE_UP, mc_game.event_MouseUp);
			
			//removeChild(mc_playerLeiste);
			removeChild(mc_game);
			
			Mouse.show();
		}		
		
		public function update(e:Event):void
		{
			
		
			// update counter and limit framerate
			/*m_fpsCounter.update();
			FRateLimiter.limitFrame(100);*/
		}
	}
}













