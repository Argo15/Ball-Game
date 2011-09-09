import java.awt.*;
import java.awt.event.*;

import javax.media.opengl.*;
import javax.media.opengl.glu.*;
import javax.swing.JFrame;
import com.sun.opengl.util.*;
import java.nio.ByteBuffer;

public class BallGame extends JFrame implements GLEventListener, KeyListener, MouseListener, MouseMotionListener, ActionListener{

	// mouse control variables
	private final GLCanvas canvas;
	private int winW = 512, winH = 512;

	private GL gl;
	private final GLU glu = new GLU();
	private final GLUT glut = new GLUT();

	public static void main(String args[]) {
		new BallGame();
	}

	// constructor
	public BallGame() {
		super("Ball Game");
		canvas = new GLCanvas();
		canvas.addGLEventListener(this);
		canvas.addKeyListener(this);
		canvas.addMouseListener(this);
		canvas.addMouseMotionListener(this);
		getContentPane().add(canvas);
		setSize(winW, winH);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setVisible(true);
		canvas.requestFocus();
	}
	
	// gl display function
	public void display(GLAutoDrawable drawable) {
		gl.glClear(GL.GL_COLOR_BUFFER_BIT | GL.GL_DEPTH_BUFFER_BIT);
		gl.glEnable(GL.GL_LIGHTING);
	}

	public void init(GLAutoDrawable drawable) {
		gl = drawable.getGL();
    		gl.setSwapInterval(1);

		gl.glColorMaterial(GL.GL_FRONT, GL.GL_DIFFUSE);
		gl.glEnable( GL.GL_COLOR_MATERIAL ) ;
		gl.glEnable(GL.GL_LIGHT0);
		gl.glEnable(GL.GL_NORMALIZE);
		gl.glShadeModel(GL.GL_SMOOTH);
		gl.glEnable(GL.GL_DEPTH_TEST);
		gl.glDepthFunc(GL.GL_LESS);
		gl.glCullFace(GL.GL_BACK);
		gl.glEnable(GL.GL_CULL_FACE);

		gl.glClearColor(0.0f, 0.0f, 0.0f, 1f);
		gl.glClearDepth(1.0f);
	}

	public void reshape(GLAutoDrawable drawable, int x, int y, int width, int height) {
		winW = width;
		winH = height;

		gl.glMatrixMode(GL.GL_PROJECTION);
		gl.glLoadIdentity();
		glu.gluPerspective(45.0f, (float) width / (float) height, 0.01f, 100.0f);
		gl.glViewport(0, 0, width, height);
		gl.glMatrixMode(GL.GL_MODELVIEW);		
	}
        
        public void displayChanged(GLAutoDrawable drawable, boolean modeChanged, boolean deviceChanged) { }
        
	public void mousePressed(MouseEvent e) { }
	public void mouseReleased(MouseEvent e) { }
	public void mouseDragged(MouseEvent e) { }
	public void keyPressed(KeyEvent e) { }
	public void keyTyped(KeyEvent e) { }
	public void keyReleased(KeyEvent e) { }
	public void mouseMoved(MouseEvent e) { }
	public void actionPerformed(ActionEvent e) { }
	public void mouseClicked(MouseEvent e) { }
	public void mouseEntered(MouseEvent e) { }
	public void mouseExited(MouseEvent e) {	}

}
