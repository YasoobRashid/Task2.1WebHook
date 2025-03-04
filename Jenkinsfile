pipeline {
    agent any

    environment {
        DIRECTORY_PATH = "https://github.com/YasoobRashid/Task2.1WebHook"
        TESTING_ENVIRONMENT = "Test-Env"
        PRODUCTION_ENVIRONMENT = "Yasoob"
    }

    stages {
        stage('Build') {
            steps {
                echo "Fetch the source code from ${env.DIRECTORY_PATH}"
                echo "Compile the code and generate any necessary artifacts"
            }
        }
        stage('Test') {
            steps {
                echo "Unit tests"
                echo "Integration tests"
            }
        }
        stage('Code Quality Check') {
            steps {
                echo "Check the quality of the code"
            }
        }
        stage('Deploy') {
            steps {
                echo "Deploy the application to ${env.TESTING_ENVIRONMENT}"
            }
        }
        stage('Approval') {
            steps {
                echo "Waiting for manual approval..."
                sleep 10
            }
        }
        stage('Deploy to Production') {
            steps {
                echo "Deploying to production: ${env.PRODUCTION_ENVIRONMENT}"
            }
        }
    }
}
