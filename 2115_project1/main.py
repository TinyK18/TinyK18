class TokenType:
    LPAREN = 'LPAREN '  # ’( ’
    RPAREN = 'RPAREN '  # ’) ’
    COMMA = 'COMMA'  # ’,’
    COLON = 'COLON '  # ’: ’
    SEMICOLON = ' SEMICOLON '  # ’; ’
    STRING = 'STRING'  # Tree leaves or node names
    NUMBER = 'NUMBER'  # Edge lengths or numeric values
    EOF = 'EOF'  # End of inpu\
    PLUS = 'PLUS'  # '+'
    MINUS = 'MINUS'  # '-'
    MULTIPLY = 'MULTIPLY'  # '*'
    DIVIDE = 'DIVIDE'  # '/'
    LBRACKET = 'LBRACKET'  # '['
    RBRACKET = 'RBRACKET'  # ']'
    LBRACE = 'LBRACE'  # '{'
    RBRACE = 'RBRACE'  # '}'
    Booleans = 'Booleans' #true/false
    Empty = 'EMPTY'


class Token:
    def __init__(self, type_, value=None):  # The default value of value is None

        self.type = type_
        self.value = value

    def __repr__(self):  # Official writing
        return f"<Token({self.type},{self.value} )>"


class LexerError(Exception):
    # Inherits Python's built-in Exception class
    def __init__(self, position, char):
        self.position = position
        self.char = char
        super().__init__(f"Invalic character {char} at {position}")
    # Used to initialize the parent class and pass a custom error message to the parent class's constructor.


class Scanner:
    def __init__(self, input_txt):
        self.input = input_txt
        self.position = 0
        if input_txt:
            self.current_content = self.input[self.position]
        else:
            self.current_content = None

    # self.current_char = self.input_text[self.position] if input_text else None

    # input Buffer
    def advance(self):
        self.position += 1
        if len(self.input) <= self.position:
            self.current_content = None
        else:
            self.current_content = self.input[self.position]

    def skip_space(self):
        while self.current_content is not None and self.current_content.isspace():
            self.advance()

    def recognize_num(self):
        # Scientific notation
        # 1e+123 => 1 * 10^123
        result = ''
        while self.current_content is not None and (self.current_content.isdigit() or self.current_content == "."):
            result += self.current_content
            self.advance()
        #
        if self.current_content in ['e', 'E']:
            result += self.current_content
            self.advance()
            if self.current_content in ['-', '+']:
                result += self.current_content
                self.advance()
            while self.current_content is not None and (self.current_content.isdigit() or self.current_content == "."):
                # float(result)This will convert the string to a Python floating point number.
                result += self.current_content
                self.advance()

        # This means that the function call will return an instance of the Token class.
        return Token(TokenType.NUMBER, float(result))

    def recognize_str(self):
        result = ''
        # isalnum()Function to determine letters and numbers but built-in function
        x=self.current_content
        if(self.current_content == '"' or self.current_content == "'"):
            self.advance()
        while self.current_content is not None and (self.current_content.isalnum() or self.current_content == '_' ) and self.current_content!= x:
            result += self.current_content
            self.advance()
        if(self.current_content == x):
            self.advance()
        if(result=="false" or result== "true" or result=="FALSE" or result=="TRUE"):
            return Token(TokenType.Booleans, result)
        if(result=="null"):
            return Token(TokenType.Empty, result)
        return Token(TokenType.STRING, result)

    def getNextToken(self):
        while self.current_content is not None:
            if self.current_content.isspace():
                self.skip_space()
                continue
                # Skip the rest of the current loop, and start the next loop if it is an empty square
            if self.current_content == '+':
                self.advance()
                return Token(TokenType.PLUS, '+')
            if self.current_content == '[':
                self.advance()
                return Token(TokenType.LBRACKET, '[')
            if self.current_content == ']':
                self.advance()
                return Token(TokenType.RBRACKET, ']')
            if self.current_content == '{':
                self.advance()
                return Token(TokenType.LBRACE, '{')
            if self.current_content == '}':
                self.advance()
                return Token(TokenType.RBRACE, '}')
            if self.current_content == '-':
                self.advance()
                return Token(TokenType.MINUS, '-')
            if self.current_content == '*':
                self.advance()
                return Token(TokenType.MULTIPLY, '*')
            if self.current_content == '/':
                self.advance()
                return Token(TokenType.DIVIDE, '/')
            if self.current_content == '(':
                self.advance()
                return Token(TokenType.LPAREN, '(')
            if self.current_content == ')':
                self.advance()
                return Token(TokenType.RPAREN, ')')
            if self.current_content == ',':
                self.advance()
                return Token(TokenType.COMMA, ',')
            if self.current_content == ';':
                self.advance()
                return Token(TokenType.SEMICOLON, ';')
            if self.current_content == ':':
                self.advance()
                return Token(TokenType.COLON, ':')
            if self.current_content.isdigit() or self.current_content == '.' :
                return self.recognize_num()
            if self.current_content.isalnum() or self.current_content == '_' or self.current_content == '"' or self.current_content == "'":
                return self.recognize_str()

            raise LexerError(self.position,self.current_content)
            #If it cannot be recognized, an error is thrown
        return Token(TokenType.EOF, None)


if __name__ == "__main__":
    input_text = input("Please input your text(like '(2e+3 + 8) * 23'):")
    scan = Scanner(input_text)

    token = scan.getNextToken()
    while token.type != TokenType.EOF:
        print(token)
        token = scan.getNextToken()













