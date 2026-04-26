import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import 'bootstrap/dist/css/bootstrap.min.css';
import App from './App.jsx'
import initModule from './wasm/CivicEngine.js'

const Module = await initModule()

createRoot(document.getElementById('root')).render(
  <StrictMode>
    <App Module={Module}/>
  </StrictMode>,
)
