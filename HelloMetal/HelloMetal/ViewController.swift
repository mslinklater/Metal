import UIKit
import Metal

class ViewController: UIViewController {
  var device: MTLDevice!
  var metalLayer: CAMetalLayer!
  var vertexBuffer: MTLBuffer!
  var pipelineState: MTLRenderPipelineState!
  var commandQueue: MTLCommandQueue!
  var timer: CADisplayLink!
  
  let vertexData: [Float] = [
    0.0, 1.0, 0.0,
    -1.0, -1.0, 0.0,
    1.0, -1.0, 0.0
  ]
  
  override func viewDidLoad() {
    // grab the Metal device
    device = MTLCreateSystemDefaultDevice()
    
    // setup the Metal CALayer
    metalLayer = CAMetalLayer()
    metalLayer.device = device
    metalLayer.pixelFormat = .bgra8Unorm
    metalLayer.framebufferOnly = true
    metalLayer.frame = view.layer.frame
    view.layer.addSublayer(metalLayer)
    
    // setup the vertex buffer
    let dataSize = vertexData.count * MemoryLayout.size(ofValue: vertexData[0])
    vertexBuffer = device.makeBuffer(bytes: vertexData, length: dataSize, options: [])
    
    // initialise the shaders
    let defaultLibrary = device.makeDefaultLibrary()!
    let fragmentProgram = defaultLibrary.makeFunction(name: "basic_fragment")
    let vertexProgram = defaultLibrary.makeFunction(name: "basic_vertex")
    
    // setup the render pipeline state
    let pipelineStateDescriptor = MTLRenderPipelineDescriptor()
    pipelineStateDescriptor.vertexFunction = vertexProgram
    pipelineStateDescriptor.fragmentFunction = fragmentProgram
    pipelineStateDescriptor.colorAttachments[0].pixelFormat = .bgra8Unorm
    
    // create the pipeline state
    pipelineState = try! device.makeRenderPipelineState(descriptor: pipelineStateDescriptor)
    
    // create a command queue
    commandQueue = device.makeCommandQueue()
    
    // setup the display link timer - for refresh
    timer = CADisplayLink(target: self, selector: #selector(gameLoop))
    timer.add(to: RunLoop.main, forMode: .default)
  }
  
  func render() {
    // grab the next render surface
    guard let drawable = metalLayer?.nextDrawable() else { return }
    
    // setup the render pass
    let renderPassDescriptor = MTLRenderPassDescriptor()
    renderPassDescriptor.colorAttachments[0].texture = drawable.texture
    renderPassDescriptor.colorAttachments[0].loadAction = .clear
    renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColor(red: 0.0, green: 104.0/255.0, blue: 55.0/255.0, alpha: 1.0)
    
    // create a command buffer
    let commandBuffer = commandQueue.makeCommandBuffer()!
    
    // create a render command encoder
    let renderEncoder = commandBuffer.makeRenderCommandEncoder(descriptor: renderPassDescriptor)!
    renderEncoder.setRenderPipelineState(pipelineState)
    renderEncoder.setVertexBuffer(vertexBuffer, offset: 0, index: 0)
    renderEncoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 3, instanceCount: 1)
    renderEncoder.endEncoding()
    
    //
    commandBuffer.present(drawable)
    commandBuffer.commit()
  }
  
  @objc func gameLoop() {
    autoreleasepool {
      self.render()
    }
  }
}
