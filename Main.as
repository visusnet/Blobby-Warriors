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
		var mc_playerLeiste:playerLeiste = new playerLeiste();
		var mc_border:border = new border();

												
		
		public function Main()
		{
			// Events
			addEventListener(Event.ENTER_FRAME, update, false, 0, true);

			//trace("loool");
			//addChild(mc_game);
			
			//addChild(mc_border);
			addChildAt(mc_border, 0);
			addChild(mc_mainMenue);
			
			
			//removeChild(mc_game);
		}
		
		public function startGame()
		{
			mc_mainMenue.visible = false;			

			
			mc_game = new BGame();
			stage.addEventListener(KeyboardEvent.KEY_DOWN, mc_game.event_KeyDown);
			stage.addEventListener(KeyboardEvent.KEY_UP, mc_game.event_KeyUp);
			addEventListener(MouseEvent.MOUSE_MOVE, mc_game.event_MouseMove);
			addEventListener(MouseEvent.MOUSE_DOWN, mc_game.event_MouseDown);
			addEventListener(MouseEvent.MOUSE_UP, mc_game.event_MouseUp);
			
			addChild(mc_game);
			addChild(mc_playerLeiste);
			
			mc_playerLeiste.y = 600-89;
			
			Mouse.hide();
		}		
		
		public function stopGame()
		{
			mc_mainMenue.visible = true;
			
			stage.removeEventListener(KeyboardEvent.KEY_DOWN, mc_game.event_KeyDown);
			
			removeChild(mc_playerLeiste);
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













