use winit::{
    event::*,
    event_loop::{ControlFlow, EventLoop},
    window::WindowBuilder,
};

#[derive(Debug)]
struct Vector4 {
    x: f32,
    y: f32,
    z: f32,
    w: f32,
}

struct Vector4Widget {
    position: (f64, f64),
    size: (f64, f64),
    value: Vector4,
}

impl Vector4Widget {
    fn new(position: (f64, f64), size: (f64, f64), value: Vector4) -> Self {
        Self {
            position,
            size,
            value,
        }
    }

    fn handle_event(&mut self, event: &WindowEvent) {
        match event {
            WindowEvent::CursorMoved { position, .. } => {
                let x = (position.x - self.position.0) as f32 / self.size.0 as f32;
                let y = (position.y - self.position.1) as f32 / self.size.1 as f32;
                self.value = Vector4 {
                    x,
                    y,
                    z: 0.0,
                    w: 1.0,
                };
                // Fire an event to indicate that the value has changed
                // You could use a channel, a callback, or any other mechanism that fits your use case
                println!("New value: {:?}", self.value);
            }
            _ => {}
        }
    }
}

pub fn run2() {
    let event_loop = EventLoop::new();
    let window = WindowBuilder::new()
        .with_title("Vector4 Widget")
        .with_inner_size(winit::dpi::LogicalSize::new(400, 400))
        .build(&event_loop)
        .unwrap();

    let mut widget = Vector4Widget::new(
        (100.0, 100.0),
        (200.0, 200.0),
        Vector4 {
            x: 0.5,
            y: 0.5,
            z: 0.0,
            w: 1.0,
        },
    );

    event_loop.run(move |event, _, control_flow| {
        *control_flow = ControlFlow::Poll;

        match event {
            Event::WindowEvent { event, .. } => {
                widget.handle_event(&event);
                match event {
                    WindowEvent::CloseRequested => {
                        *control_flow = ControlFlow::Exit;
                    }
                    _ => {}
                }
            }
            _ => {}
        }
    });
}

#[cfg(target_arch = "wasm32")]
use wasm_bindgen::prelude::*;

#[cfg_attr(target_arch = "wasm32", wasm_bindgen(start))]
pub fn run() {
    cfg_if::cfg_if! {
        if #[cfg(target_arch = "wasm32")] {
            std::panic::set_hook(Box::new(console_error_panic_hook::hook));
            console_log::init_with_level(log::Level::Warn).expect("Couldn't initialize logger");
        } else {
            env_logger::init();
        }
    }

    let event_loop = EventLoop::new();
    let window = WindowBuilder::new().build(&event_loop).unwrap();

    #[cfg(target_arch = "wasm32")]
    {
        // Winit prevents sizing with CSS, so we have to set
        // the size manually when on web.
        use winit::dpi::PhysicalSize;
        window.set_inner_size(PhysicalSize::new(450, 400));

        use winit::platform::web::WindowExtWebSys;
        web_sys::window()
            .and_then(|win| win.document())
            .and_then(|doc| {
                let dst = doc.get_element_by_id("wasm-example")?;
                let canvas = web_sys::Element::from(window.canvas());
                dst.append_child(&canvas).ok()?;
                Some(())
            })
            .expect("Couldn't append canvas to document body.");
    }

    event_loop.run(move |event, _, control_flow| match event {
        Event::WindowEvent {
            ref event,
            window_id,
        } if window_id == window.id() => match event {
            WindowEvent::CloseRequested
            | WindowEvent::KeyboardInput {
                input:
                    KeyboardInput {
                        state: ElementState::Pressed,
                        virtual_keycode: Some(VirtualKeyCode::Escape),
                        ..
                    },
                ..
            } => *control_flow = ControlFlow::Exit,
            _ => {}
        },
        _ => {}
    });
}
