import Speedometer from "./components/Speedometer";
import {Container, Row, Col} from "react-bootstrap";

function App() {
    const speed = 120; // Example speed value

    return (
      <Container className="mt-5">
        <Row>
          <Col xs="auto">
            <Speedometer speed={speed} />
          </Col>
          {/* Add more components here as needed */}
        </Row>
      </Container>
    );
}

export default App;

